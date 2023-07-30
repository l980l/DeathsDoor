#include "pch.h"
#include "CPhysXMgr.h"
#include "CTimeMgr.h"
#include "components.h"

// ���� ����
physx::PxDefaultErrorCallback   mDefaultErrorCallback;
physx::PxDefaultAllocator       mDefaultAllocatorCallback;
physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
physx::PxTolerancesScale        mToleranceScale;

physx::PxFoundation* mFoundation = NULL;
physx::PxPhysics* mPhysics = NULL;

physx::PxScene* mScene = NULL;
physx::PxMaterial* mMaterial = NULL;

physx::PxPvd* mPvd = NULL;
physx::PxCooking* mCooking = NULL;
physx::PxPvdTransport* mTransport = NULL;


CPhysXMgr::CPhysXMgr()
{
}

CPhysXMgr::~CPhysXMgr()
{
    // Cleanup
    mDispatcher->release();
    mScene->release();
    mMaterial->release();
    mPhysics->release();

    if (mPvd)
    {
        mPvd->release();
        mPvd = nullptr;
    }
    mCooking->release();
    mTransport->release();
    mFoundation->release();
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
    mTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*mTransport, physx::PxPvdInstrumentationFlag::eALL);

    mToleranceScale.length = 100;   // typical length of an object;
    mToleranceScale.speed = 981;    // typical speed of an object, gravity*1s is a reasonable choice;

    // Physics init (PhysX �ֿ� ����� �����ϴ� ��ü��, ���� ���, ��ü, ���� ���� �����ϴ� ����� ����)
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
    if (!mPhysics)
        MessageBoxA(nullptr, "Error", "PxCreatePhysics failed!", MB_OK);

    // Physics ��ü���� ��ŷ ��ü ����
    physx::PxCookingParams mParam(mToleranceScale);
    mParam.meshWeldTolerance = 0.001f;
    mParam.meshPreprocessParams = physx::PxMeshPreprocessingFlags(physx::PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH); // Disable mesh cleaning
    mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, mParam);

    // Create scene
    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = mDispatcher;
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
    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1f);

    // ============
    // Create actor
    // ============

   // PxCreatePlane
   // ���� ��� ����, PxPlane(0, 1, 0, 0)�� ����� �������� ��Ÿ���µ�, �� ��� y���� ���� ������ ���ϴ� ���� ����� ��Ÿ��
   // *mMaterial�� �� ����� ������ �Ӽ�(������, �ݹ߷� ��)�� �����ϴ� ������ ��Ÿ��.
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
    };
}

physx::PxRigidDynamic* CPhysXMgr::CreateDynamic(const PxTransform& t, const PxGeometry& geometry, CGameObject* _Object, const PxVec3& velocity)
{
    if (nullptr == _Object)
        assert(nullptr);

    m_vecDynamicObject.push_back(_Object);

    physx::PxRigidDynamic* dynamic = PxCreateDynamic(*mPhysics, t, geometry, *mMaterial, 10.0f);
    dynamic->setAngularDamping(0.5f);       // ��ü�� ȸ���� �� �󸶳� ���� �ӵ��� �پ������� ����
    dynamic->setLinearVelocity(velocity);   // ��ü�� ���ӵ�, ��ü�� �󸶳� ���� �̵��ϴ����� ����
    mScene->addActor(*dynamic);             // ���� �ش� ���� �߰�
    m_vecDynamicActor.push_back(dynamic);

    return dynamic;
}

physx::PxRigidStatic* CPhysXMgr::ConvertStatic(const PxTransform& t, const PxGeometry& geometry, CGameObject* _Object, const PxVec3& velocity)
{

    // Mesh�� ���� ������ �־���
    Ptr<CMesh> pMesh = _Object->GetRenderComponent()->GetMesh();
    PxTriangleMeshDesc  meshDesc;
    meshDesc.points.count = pMesh->GetVtxCount();
    meshDesc.points.stride = sizeof(Vtx);
    meshDesc.points.data = pMesh->GetVtxSysMem();

    // Mesh�� Idx ���� ������ �־���
    meshDesc.triangles.count = pMesh->GetIdxInfo(0).iIdxCount / 3;
    meshDesc.triangles.stride = 3 * sizeof(UINT);
    meshDesc.triangles.data = pMesh->GetIdxInfo(0).pIdxSysMem;

    // Physx������ Mesh�� �����ϴ� ���� Cooking�̶�� ��.
    // Mesh������ ���� write ���� �� ������� �޾Ƴ��� ��ü ����
    PxDefaultMemoryOutputStream  writeBuffer;
    PxTriangleMeshCookingResult::Enum  result;
    bool  state = mCooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
    // �����Ѵٸ� null ��ȯ
    if (!state)
        return NULL;
    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());


    // �޾ƿ� Mesh ������ ���� ���۷� ��������Ʈ�� 3�� ����ϴ� TriangleMesh�� ����
    PxTriangleMesh* tMesh = mPhysics->createTriangleMesh(readBuffer);
    PxTriangleMeshGeometry meshGeometry(tMesh);
    PxShape* meshShape = mPhysics->createShape(meshGeometry, *mMaterial);

    // Mesh ������ Mtrl�� ���� ���޹��� Mesh ��� Shape�� ������ Actor�� ������ ������.
    PxRigidStatic* pActor = mPhysics->createRigidStatic(t);
    pActor->attachShape(*meshShape);
    // Scean�� Actor ���
    mScene->addActor(*pActor);
    meshShape->release();
    m_vecStaticActor.push_back(pActor);

    return pActor;

}

PxRigidStatic* CPhysXMgr::CreatePlane(Vec4 _Plane)
{
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(_Plane.x, _Plane.y, _Plane.z, _Plane.w), *mMaterial);
    mScene->addActor(*groundPlane);
    return groundPlane;
}

void CPhysXMgr::Clear()
{
    for (size_t i = 0; i < m_vecDynamicActor.size(); ++i)
    {
        if(nullptr != m_vecDynamicActor[i])
            m_vecDynamicActor[i]->release();
    }

    for (size_t i = 0; i < m_vecStaticActor.size(); ++i)
    {
        if (nullptr != m_vecStaticActor[i])
            m_vecStaticActor[i]->release();
    }

    m_vecDynamicObject.clear();
}
