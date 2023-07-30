#include "pch.h"
#include "CPhysXMgr.h"
#include "CTimeMgr.h"
#include "components.h"

// 변수 선언
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
    // Foundation init (메모리 할당, 오류 보고, 디버그 출력 등의 기능을 제공)
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
    if (!mFoundation)
        MessageBoxA(nullptr, "Error", "PxCreateFoundation failed!", MB_OK);

    // PhysX Visual Debugger init
    mPvd = PxCreatePvd(*mFoundation);
    mTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*mTransport, physx::PxPvdInstrumentationFlag::eALL);

    mToleranceScale.length = 100;   // typical length of an object;
    mToleranceScale.speed = 981;    // typical speed of an object, gravity*1s is a reasonable choice;

    // Physics init (PhysX 주요 기능을 제공하는 객체로, 물리 장면, 물체, 물질 등을 생성하는 기능을 제공)
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
    if (!mPhysics)
        MessageBoxA(nullptr, "Error", "PxCreatePhysics failed!", MB_OK);

    // Physics 객체에서 쿠킹 객체 생성
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

    // Create material (물리 객체 표면의 마찰력, 반탄력 등 설정)
    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1f);

    // ============
    // Create actor
    // ============

   // PxCreatePlane
   // 지면 평면 생성, PxPlane(0, 1, 0, 0)는 평면의 방정식을 나타내는데, 이 경우 y축을 따라 위쪽을 향하는 수평 평면을 나타냄
   // *mMaterial는 이 평면의 물리적 속성(마찰력, 반발력 등)을 정의하는 물질을 나타냄.
   //physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *mMaterial);
   //mScene->addActor(*groundPlane);

    //// 동적 물체 생성, #1 위치, #2 물체 모양, #3 속도(기본값 0)
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
    dynamic->setAngularDamping(0.5f);       // 물체가 회전할 때 얼마나 빨리 속도가 줄어드는지를 결정
    dynamic->setLinearVelocity(velocity);   // 물체의 선속도, 물체가 얼마나 빨리 이동하는지를 결정
    mScene->addActor(*dynamic);             // 씬에 해당 액터 추가
    m_vecDynamicActor.push_back(dynamic);

    return dynamic;
}

physx::PxRigidStatic* CPhysXMgr::ConvertStatic(const PxTransform& t, const PxGeometry& geometry, CGameObject* _Object, const PxVec3& velocity)
{

    // Mesh의 정점 정보를 넣어줌
    Ptr<CMesh> pMesh = _Object->GetRenderComponent()->GetMesh();
    PxTriangleMeshDesc  meshDesc;
    meshDesc.points.count = pMesh->GetVtxCount();
    meshDesc.points.stride = sizeof(Vtx);
    meshDesc.points.data = pMesh->GetVtxSysMem();

    // Mesh의 Idx 버퍼 정보를 넣어줌
    meshDesc.triangles.count = pMesh->GetIdxInfo(0).iIdxCount / 3;
    meshDesc.triangles.stride = 3 * sizeof(UINT);
    meshDesc.triangles.data = pMesh->GetIdxInfo(0).pIdxSysMem;

    // Physx에서는 Mesh를 생성하는 것을 Cooking이라고 함.
    // Mesh생성을 위한 write 버퍼 및 결과값을 받아내는 객체 생성
    PxDefaultMemoryOutputStream  writeBuffer;
    PxTriangleMeshCookingResult::Enum  result;
    bool  state = mCooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
    // 실패한다면 null 반환
    if (!state)
        return NULL;
    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());


    // 받아온 Mesh 정보를 담은 버퍼로 정점포인트를 3개 사용하는 TriangleMesh를 생성
    PxTriangleMesh* tMesh = mPhysics->createTriangleMesh(readBuffer);
    PxTriangleMeshGeometry meshGeometry(tMesh);
    PxShape* meshShape = mPhysics->createShape(meshGeometry, *mMaterial);

    // Mesh 정보와 Mtrl을 통해 전달받은 Mesh 모양 Shape을 생성해 Actor를 생성해 입혀줌.
    PxRigidStatic* pActor = mPhysics->createRigidStatic(t);
    pActor->attachShape(*meshShape);
    // Scean에 Actor 등록
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
