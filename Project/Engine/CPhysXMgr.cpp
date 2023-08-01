#include "pch.h"
#include "CPhysXMgr.h"
#include "CTimeMgr.h"
#include "components.h"

CPhysXMgr::CPhysXMgr()
    : m_vecDynamicObject{}
    , m_vecDynamicActor{}
    , m_vecStaticActor{}
    , m_fUpdateTime(0.f)
{
}

CPhysXMgr::~CPhysXMgr()
{
    // Cleanup
    m_Dispatcher->release();
    m_Scene->release();
    m_Material->release();
    m_Physics->release();

    if (m_Pvd)
    {
        m_Pvd->release();
        m_Pvd = nullptr;
    }
    m_Cooking->release();
    m_Transport->release();
    m_Foundation->release();
}

void CPhysXMgr::init()
{
    // Init PhysX
    // Foundation init (메모리 할당, 오류 보고, 디버그 출력 등의 기능을 제공)
    m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_DefaultAllocatorCallback, m_DefaultErrorCallback);
    if (!m_Foundation)
        MessageBoxA(nullptr, "Error", "PxCreateFoundation failed!", MB_OK);

    // PhysX Visual Debugger init
    m_Pvd = PxCreatePvd(*m_Foundation);
    m_Transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    m_Pvd->connect(*m_Transport, physx::PxPvdInstrumentationFlag::eALL);

    m_ToleranceScale.length = 100;   // typical length of an object;
    m_ToleranceScale.speed = 981;    // typical speed of an object, gravity*1s is a reasonable choice;

    // Physics init (PhysX 주요 기능을 제공하는 객체로, 물리 장면, 물체, 물질 등을 생성하는 기능을 제공)
    m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, m_ToleranceScale, true, m_Pvd);
    if (!m_Physics)
        MessageBoxA(nullptr, "Error", "PxCreatePhysics failed!", MB_OK);

    // Physics 객체에서 쿠킹 객체 생성
    // Mesh를 가져오는 것을 cook이라고 함.
    physx::PxCookingParams mParam(m_ToleranceScale);
    mParam.meshWeldTolerance = 0.001f;
    mParam.meshPreprocessParams = physx::PxMeshPreprocessingFlags(physx::PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH); // Disable mesh cleaning
    m_Cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_Foundation, mParam);

    // Create scene
    physx::PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    m_Dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = m_Dispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    m_Scene = m_Physics->createScene(sceneDesc);

    physx::PxPvdSceneClient* pvdClient = m_Scene->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    // Create material (물리 객체 표면의 마찰력, 반탄력 등 설정)
    m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.2f);

   // PxCreatePlane
   // 지면 평면 생성, PxPlane(0, 1, 0, 0)는 평면의 방정식을 나타내는데, 이 경우 y축을 따라 위쪽을 향하는 수평 평면을 나타냄
   // *mMaterial는 이 평면의 물리적 속성(마찰력, 반발력 등)을 정의하는 물질을 나타냄.
   //physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*m_Physics, physx::PxPlane(0.f, 1.f, 0.f, 0.f), *m_Material);
   //m_Scene->addActor(*groundPlane);
    //// 동적 물체 생성, #1 위치, #2 물체 모양, #3 속도(기본값 0)
    //CreateDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
}

void CPhysXMgr::tick()
{
    // Run simulation
    m_Scene->simulate(DT);
    m_fUpdateTime += DT;
    if(m_fUpdateTime > 0.1f)
    {
        m_Scene->fetchResults(true);
        m_fUpdateTime = 0.f;
    }
    else
        m_Scene->fetchResults(false);

    for (size_t i = 0; i < m_vecDynamicActor.size(); ++i)
    {
        if (nullptr == m_vecDynamicActor[i])
            continue;
        m_vecDynamicObject[i]->Rigidbody()->AddForce(Vec3(0.f, -100.f * DT, 0.f));
        PxTransform GlobalPose = m_vecDynamicActor[i]->getGlobalPose();
        m_vecDynamicObject[i]->Transform()->SetRelativePos(Vec3(GlobalPose.p.x, GlobalPose.p.y, GlobalPose.p.z));
    };
}

physx::PxRigidDynamic* CPhysXMgr::CreateDynamic(Vec3 _vSpawnPos, const PxGeometry& _Geometry, CGameObject* _Object, const PxVec3& _Velocity)
{
    if (nullptr == _Object)
        assert(nullptr);

    const PxTransform& SpawnPos = PxTransform(_vSpawnPos.x, _vSpawnPos.y, _vSpawnPos.z);

    m_vecDynamicObject.push_back(_Object);

    physx::PxRigidDynamic* dynamic = PxCreateDynamic(*m_Physics, SpawnPos, _Geometry, *m_Material, 10.f);
    dynamic->setAngularDamping(0.f);       // 물체가 회전할 때 얼마나 빨리 속도가 줄어드는지를 결정
    dynamic->setLinearVelocity(_Velocity);   // 물체의 선속도, 물체가 얼마나 빨리 이동하는지를 결정
    dynamic->setMaxDepenetrationVelocity(30.f);
    dynamic->setMass(10.f);
    m_Scene->addActor(*dynamic);             // 씬에 해당 액터 추가
    m_vecDynamicActor.push_back(dynamic);
    _Object->Rigidbody()->SetRigidbody(dynamic);

    return dynamic;
}

physx::PxRigidDynamic* CPhysXMgr::CreateCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object, Vec3 _vVelocity)
{
    const PxBoxGeometry& BoxGeometry = PxBoxGeometry(_vCubeScale.x, _vCubeScale.y, _vCubeScale.z);
    const PxVec3& Velocity = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    return CreateDynamic(_vSpawnPos, BoxGeometry, _Object, Velocity);
}

physx::PxRigidDynamic* CPhysXMgr::CreateCapsule(Vec3 _vSpawnPos, float _fRadius, float _fHeight, CGameObject* _Object, Vec3 _vVelocity)
{
    const PxCapsuleGeometry& CapsuleGeometry = PxCapsuleGeometry(_fRadius, _fHeight);
    const PxVec3& Velocity = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    return CreateDynamic(_vSpawnPos, CapsuleGeometry, _Object, Velocity);
}

physx::PxRigidDynamic* CPhysXMgr::CreateSphere(Vec3 _vSpawnPos, float _fRadius, CGameObject* _Object, Vec3 _vVelocity)
{
    const PxSphereGeometry& SphereGeometry = PxSphereGeometry(_fRadius);
    const PxVec3& Velocity = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    return CreateDynamic(_vSpawnPos, SphereGeometry, _Object, Velocity);
}

physx::PxRigidStatic* CPhysXMgr::ConvertStatic(Vec3 _vSpawnPos, CGameObject* _Object)
{
    const PxTransform& SpawnPos = PxTransform(_vSpawnPos.x, _vSpawnPos.y, _vSpawnPos.z);
    // Mesh의 정점 정보를 넣어줌
    Ptr<CMesh> pMesh = _Object->GetRenderComponent()->GetMesh();
    PxTriangleMeshDesc  meshDesc;
    meshDesc.points.count = pMesh->GetVtxCount();
    meshDesc.points.stride = sizeof(Vtx);
    meshDesc.points.data = pMesh->GetVtxSysMem();
    // Mesh의 Idx 버퍼 정보를 넣어줌
    meshDesc.triangles.count = pMesh->GetIdxInfo(0).iIdxCount / 3;;
    meshDesc.triangles.stride = 3 * sizeof(UINT);
    meshDesc.triangles.data = pMesh->GetIdxInfo(0).pIdxSysMem;

    // Physx에서는 Mesh를 생성하는 것을 Cooking이라고 함.
    // Mesh생성을 위한 write 버퍼 및 결과값을 받아내는 객체 생성
    PxDefaultMemoryOutputStream  writeBuffer;
    PxTriangleMeshCookingResult::Enum  result;
    bool  state = m_Cooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
    // 실패한다면 null 반환
    if (!state)
        assert(NULL);
    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());

    // 받아온 Mesh 정보를 담은 버퍼로 정점포인트를 3개 사용하는 TriangleMesh를 생성
    PxTriangleMesh* tMesh = m_Physics->createTriangleMesh(readBuffer);
    PxTriangleMeshGeometry meshGeometry(tMesh);
    PxShape* meshShape = m_Physics->createShape(meshGeometry, *m_Material);

    // Mesh 정보와 Mtrl을 통해 전달받은 Mesh 모양 Shape을 생성해 Actor를 생성해 입혀줌.
    PxRigidStatic* pActor = m_Physics->createRigidStatic(SpawnPos);
    pActor->attachShape(*meshShape);
    // Scean에 Actor 등록
    m_Scene->addActor(*pActor);
    m_vecStaticActor.push_back(pActor);
    meshShape->release();

    return pActor;

}

PxRigidStatic* CPhysXMgr::CreatePlane(Vec4 _Plane)
{
    // 평면의 방정식을 이용한 전체 맵에 적용되는 평면 생성
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*m_Physics, physx::PxPlane(_Plane.x, _Plane.y, _Plane.z, _Plane.w), *m_Material);
    m_Scene->addActor(*groundPlane);
    return groundPlane;
}

void CPhysXMgr::SetRenderRigidbody(bool _bRender)
{
    for (size_t i = 0; i < m_vecDynamicActor.size(); ++i)
    {
        m_vecDynamicActor[i]->setActorFlags(PxActorFlag::eVISUALIZATION);
    }

    for (size_t i = 0; i < m_vecStaticActor.size(); ++i)
    {
        m_vecStaticActor[i]->setActorFlags(PxActorFlag::eVISUALIZATION);
    }
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
