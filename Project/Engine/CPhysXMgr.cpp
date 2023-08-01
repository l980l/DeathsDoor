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
    // Foundation init (�޸� �Ҵ�, ���� ����, ����� ��� ���� ����� ����)
    m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_DefaultAllocatorCallback, m_DefaultErrorCallback);
    if (!m_Foundation)
        MessageBoxA(nullptr, "Error", "PxCreateFoundation failed!", MB_OK);

    // PhysX Visual Debugger init
    m_Pvd = PxCreatePvd(*m_Foundation);
    m_Transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    m_Pvd->connect(*m_Transport, physx::PxPvdInstrumentationFlag::eALL);

    m_ToleranceScale.length = 100;   // typical length of an object;
    m_ToleranceScale.speed = 981;    // typical speed of an object, gravity*1s is a reasonable choice;

    // Physics init (PhysX �ֿ� ����� �����ϴ� ��ü��, ���� ���, ��ü, ���� ���� �����ϴ� ����� ����)
    m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, m_ToleranceScale, true, m_Pvd);
    if (!m_Physics)
        MessageBoxA(nullptr, "Error", "PxCreatePhysics failed!", MB_OK);

    // Physics ��ü���� ��ŷ ��ü ����
    // Mesh�� �������� ���� cook�̶�� ��.
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

    // Create material (���� ��ü ǥ���� ������, ��ź�� �� ����)
    m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.2f);

   // PxCreatePlane
   // ���� ��� ����, PxPlane(0, 1, 0, 0)�� ����� �������� ��Ÿ���µ�, �� ��� y���� ���� ������ ���ϴ� ���� ����� ��Ÿ��
   // *mMaterial�� �� ����� ������ �Ӽ�(������, �ݹ߷� ��)�� �����ϴ� ������ ��Ÿ��.
   //physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*m_Physics, physx::PxPlane(0.f, 1.f, 0.f, 0.f), *m_Material);
   //m_Scene->addActor(*groundPlane);
    //// ���� ��ü ����, #1 ��ġ, #2 ��ü ���, #3 �ӵ�(�⺻�� 0)
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
    dynamic->setAngularDamping(0.f);       // ��ü�� ȸ���� �� �󸶳� ���� �ӵ��� �پ������� ����
    dynamic->setLinearVelocity(_Velocity);   // ��ü�� ���ӵ�, ��ü�� �󸶳� ���� �̵��ϴ����� ����
    dynamic->setMaxDepenetrationVelocity(30.f);
    dynamic->setMass(10.f);
    m_Scene->addActor(*dynamic);             // ���� �ش� ���� �߰�
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
    // Mesh�� ���� ������ �־���
    Ptr<CMesh> pMesh = _Object->GetRenderComponent()->GetMesh();
    PxTriangleMeshDesc  meshDesc;
    meshDesc.points.count = pMesh->GetVtxCount();
    meshDesc.points.stride = sizeof(Vtx);
    meshDesc.points.data = pMesh->GetVtxSysMem();
    // Mesh�� Idx ���� ������ �־���
    meshDesc.triangles.count = pMesh->GetIdxInfo(0).iIdxCount / 3;;
    meshDesc.triangles.stride = 3 * sizeof(UINT);
    meshDesc.triangles.data = pMesh->GetIdxInfo(0).pIdxSysMem;

    // Physx������ Mesh�� �����ϴ� ���� Cooking�̶�� ��.
    // Mesh������ ���� write ���� �� ������� �޾Ƴ��� ��ü ����
    PxDefaultMemoryOutputStream  writeBuffer;
    PxTriangleMeshCookingResult::Enum  result;
    bool  state = m_Cooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
    // �����Ѵٸ� null ��ȯ
    if (!state)
        assert(NULL);
    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());

    // �޾ƿ� Mesh ������ ���� ���۷� ��������Ʈ�� 3�� ����ϴ� TriangleMesh�� ����
    PxTriangleMesh* tMesh = m_Physics->createTriangleMesh(readBuffer);
    PxTriangleMeshGeometry meshGeometry(tMesh);
    PxShape* meshShape = m_Physics->createShape(meshGeometry, *m_Material);

    // Mesh ������ Mtrl�� ���� ���޹��� Mesh ��� Shape�� ������ Actor�� ������ ������.
    PxRigidStatic* pActor = m_Physics->createRigidStatic(SpawnPos);
    pActor->attachShape(*meshShape);
    // Scean�� Actor ���
    m_Scene->addActor(*pActor);
    m_vecStaticActor.push_back(pActor);
    meshShape->release();

    return pActor;

}

PxRigidStatic* CPhysXMgr::CreatePlane(Vec4 _Plane)
{
    // ����� �������� �̿��� ��ü �ʿ� ����Ǵ� ��� ����
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
