#include "pch.h"
#include "CPhysXMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"

using namespace physx;

// ���� ����
physx::PxDefaultErrorCallback   mDefaultErrorCallback;
physx::PxDefaultAllocator       mDefaultAllocatorCallback;
physx::PxDefaultCpuDispatcher*  mDispatcher = nullptr;
physx::PxTolerancesScale        mToleranceScale;

physx::PxFoundation* mFoundation = nullptr;
physx::PxPhysics* mPhysics = nullptr;

physx::PxScene* mScene = nullptr;
physx::PxMaterial* mMaterial = nullptr;

physx::PxPvd* mPvd = nullptr;


CPhysXMgr::CPhysXMgr()
{
}

CPhysXMgr::~CPhysXMgr()
{
    // Cleanup
    mScene->release();
    mMaterial->release();
    mPhysics->release();
    mFoundation->release();

    if (nullptr != mDispatcher)
        mDispatcher->release();

    if (mPvd)
    {
        physx::PxPvdTransport* transport = mPvd->getTransport();
        mPvd->release();
        mPvd = nullptr;

        if (transport)
        {
            transport->release();
            transport = nullptr;
        }
    }
}

void CPhysXMgr::init()
{
    // Init PhysX
    // Foundation init (�޸� �Ҵ�, ���� ����, ����� ��� ���� ����� ����)
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
    if (!mFoundation)
        MessageBoxA(nullptr, "Error", "PxCreateFoundation failed!", MB_OK);

    // PhysX Visual Debugger init
    mPvd = PxCreatePvd(*mFoundation);
    physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    // Physics init (PhysX �ֿ� ����� �����ϴ� ��ü��, ���� ���, ��ü, ���� ���� �����ϴ� ����� ����)
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
    if (!mPhysics)
        MessageBoxA(nullptr, "Error", "PxCreatePhysics failed!", MB_OK);

    // Create scene
    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    //mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    mScene = mPhysics->createScene(sceneDesc);

    physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    // Create material (���� ��ü ǥ���� ������, ��ź�� �� ����)
    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

    // ============
    // Create actor
    // ============

    //// PxCreatePlane
    //// ���� ��� ����, PxPlane(0, 1, 0, 0)�� ����� �������� ��Ÿ���µ�, �� ��� y���� ���� ������ ���ϴ� ���� ����� ��Ÿ��
    //// *mMaterial�� �� ����� ������ �Ӽ�(������, �ݹ߷� ��)�� �����ϴ� ������ ��Ÿ��.
    //physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *mMaterial);
    //mScene->addActor(*groundPlane);

    //// ���� ��ü ����, #1 ��ġ, #2 ��ü ���, #3 �ӵ�(�⺻�� 0)
    //CreateDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
}

void CPhysXMgr::tick()
{
    // Run simulation
    //mScene->simulate(DT);
    mScene->simulate(1.f / 60.f);
    mScene->fetchResults(true);

    for (size_t i = 0; i < m_vecDynamicActor.size(); ++i)
    {
        if (nullptr == m_vecDynamicActor[i])
            continue;

        PxTransform GlobalPose = m_vecDynamicActor[i]->getGlobalPose();
        m_vecDynamicObject[i]->Transform()->SetRelativePos(Vec3(GlobalPose.p.x, GlobalPose.p.y, GlobalPose.p.z));
    }

}

PxRigidDynamic* CPhysXMgr::CreateDynamic(const PxTransform& t, const PxGeometry& geometry, CGameObject* _Object, const PxVec3& velocity)
{
    if (nullptr == _Object)
        assert(nullptr);

    m_vecDynamicObject.push_back(_Object);

    PxRigidDynamic* dynamic = PxCreateDynamic(*mPhysics, t, geometry, *mMaterial, 10.0f);
    dynamic->setAngularDamping(0.5f);       // ��ü�� ȸ���� �� �󸶳� ���� �ӵ��� �پ������� ����
    dynamic->setLinearVelocity(velocity);   // ��ü�� ���ӵ�, ��ü�� �󸶳� ���� �̵��ϴ����� ����
    mScene->addActor(*dynamic);             // ���� �ش� ���� �߰�
    m_vecDynamicActor.push_back(dynamic);

    TestDynamicActor = dynamic; // �׽�Ʈ��

    return dynamic;
}

PxRigidStatic* CPhysXMgr::CreatePlane(Vec4 _Plane)
{
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(_Plane.x, _Plane.y, _Plane.z, _Plane.w), *mMaterial);
    mScene->addActor(*groundPlane);
    return groundPlane;
}