#include "pch.h"
#include "CPhysXMgr.h"
#include "CTimeMgr.h"
#include "components.h"
#include "CMeshData.h"
#include "CResMgr.h"

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
    m_Scene->setBounceThresholdVelocity(0.1f);
    physx::PxPvdSceneClient* pvdClient = m_Scene->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    // Create material (���� ��ü ǥ���� ������, ��ź�� �� ����)
    m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.f);

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
    // �ùķ��̼��� 120hz�� �ϰ� ������� 0.1�ʸ��� ������
    m_Scene->simulate(1.f / 120.f);
    m_fUpdateTime += DT;

    if(m_fUpdateTime > 0.1f)
    {
        m_Scene->fetchResults(true);
        m_fUpdateTime = 0.f;
    }
    else
        m_Scene->fetchResults(false);

    // ������� ������ Rigidbody�� ����ϴ� obj�� ��ġ���� ���������.
    // ���� Scean�� �߷��� �ſ� ���ϰ� ����ǹǷ� Velocity 300���� �߷� ��� �Ʒ��� �о���
    for (size_t i = 0; i < m_vecDynamicActor.size(); ++i)
    {
        if (nullptr == m_vecDynamicActor[i])
            continue;
        PxVec3 Velo = m_vecDynamicActor[i]->getLinearVelocity();

        if(abs(Velo.y) < 300.f)
            m_vecDynamicObject[i]->Rigidbody()->SetGravity(Velo.y - abs(Velo.y) * DT);

        PxTransform GlobalPose = m_vecDynamicActor[i]->getGlobalPose();
        m_vecDynamicObject[i]->Transform()->SetRelativePos(Vec3(GlobalPose.p.x, GlobalPose.p.y, GlobalPose.p.z));
    };
}

void CPhysXMgr::finaltick()
{
    // �� finaltick���� ������ �ִ� ���� ��ü���� IsDead ���θ� Ȯ���ϰ� �´ٸ� Scean���� ������.
    vector<CGameObject*>::iterator iter = m_vecDynamicObject.begin();
    for (; iter != m_vecDynamicObject.end(); ++iter)
    {
        CGameObject* obj = *iter;
        if(obj->IsDead())
        {
            vector<physx::PxRigidDynamic*>::iterator iteractor = m_vecDynamicActor.begin();
            for (; iteractor != m_vecDynamicActor.end(); ++iteractor)
            {
                physx::PxRigidDynamic*  actor = *iteractor;
                if (actor->getName() == string(obj->GetName().begin(), obj->GetName().end()).c_str())
                {
                    m_vecDynamicActor.erase(iteractor);
                    m_Scene->removeActor(*actor);
                }
            }
            m_vecDynamicObject.erase(iter);
        }
    }
}

physx::PxRigidDynamic* CPhysXMgr::CreateDynamic(Vec3 _vSpawnPos, const PxGeometry& _Geometry, CGameObject* _Object, float _fYOffset, const PxVec3& _Velocity)
{
    // ���� ��ü �߰�
    if (nullptr == _Object)
        assert(nullptr);

    const PxTransform& SpawnPos = PxTransform(_vSpawnPos.x, _vSpawnPos.y, _vSpawnPos.z);
    m_vecDynamicObject.push_back(_Object);
    physx::PxRigidDynamic* dynamic = PxCreateDynamic(*m_Physics, SpawnPos, _Geometry, *m_Material, 10.f);
    m_Scene->addActor(*dynamic);
    dynamic->setName(string(_Object->GetName().begin(), _Object->GetName().end()).c_str());// ���� �ش� ���� �߰�
    m_vecDynamicActor.push_back(dynamic);
    _Object->Rigidbody()->SetRigidbody(dynamic);

    return dynamic;
}

physx::PxRigidDynamic* CPhysXMgr::CreateCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object, Vec3 _vVelocity)
{
    const PxBoxGeometry& BoxGeometry = PxBoxGeometry(_vCubeScale.x, _vCubeScale.y, _vCubeScale.z);
    const PxVec3& Velocity = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    return CreateDynamic(_vSpawnPos, BoxGeometry, _Object, 0);
}

physx::PxRigidDynamic* CPhysXMgr::CreateCapsule(Vec3 _vSpawnPos, float _fRadius, float _fHeight, CGameObject* _Object, Vec3 _vVelocity)
{
    const PxCapsuleGeometry& CapsuleGeometry = PxCapsuleGeometry(_fRadius, _fHeight);
    const PxVec3& Velocity = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    return CreateDynamic(_vSpawnPos, CapsuleGeometry, _Object, 0);
}

physx::PxRigidDynamic* CPhysXMgr::CreateSphere(Vec3 _vSpawnPos, float _fRadius, CGameObject* _Object, Vec3 _vVelocity)
{
    const PxSphereGeometry& SphereGeometry = PxSphereGeometry(_fRadius);
    const PxVec3& Velocity = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    return CreateDynamic(_vSpawnPos, SphereGeometry, _Object, 0);
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
    pActor->setName(string(_Object->GetName().begin(), _Object->GetName().end()).c_str());// ���� �ش� ���� �߰�
    // Scean�� Actor ���
    m_Scene->addActor(*pActor);
    m_vecStaticActor.push_back(pActor);
    meshShape->release();
    tMesh->release();

    return pActor;

}

physx::PxRigidStatic* CPhysXMgr::CreateStaticCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object)
{
    // ���� ��ü �߰�
    if (nullptr == _Object)
        assert(nullptr);
    const PxBoxGeometry& BoxGeometry = PxBoxGeometry(_vCubeScale.x, _vCubeScale.y, _vCubeScale.z);

    const PxTransform& SpawnPos = PxTransform(_vSpawnPos.x, _vSpawnPos.y, _vSpawnPos.z);
    m_vecDynamicObject.push_back(_Object);
    physx::PxRigidStatic* Static = PxCreateStatic(*m_Physics, SpawnPos, BoxGeometry, *m_Material);
    m_Scene->addActor(*Static);
    Static->setName(string(_Object->GetName().begin(), _Object->GetName().end()).c_str());// ���� �ش� ���� �߰�
    m_vecStaticActor.push_back(Static);
    _Object->Rigidbody()->SetRigidbody(Static);

    return Static;
}

void CPhysXMgr::ReleaseStatic(wstring _strStaticName)
{
    // �߰��� ������ �ʿ䰡 �ִ� Map ��ҿ� ���� ������ �� �ִ� ���� ��ü ���� ���

    vector< PxRigidStatic*>::iterator iter = m_vecStaticActor.begin();
    for (; iter != m_vecStaticActor.end(); ++iter)
    {
        PxRigidStatic* State = *iter;
        if (State->getName() == string(_strStaticName.begin(), _strStaticName.end()).c_str())
        {
            m_vecStaticActor.erase(iter);
            m_Scene->removeActor(*State);
            return;
        }
    }
    // �ƹ��͵� �������� ���ߴٸ� assert
    assert(nullptr);
}

PxRigidStatic* CPhysXMgr::CreatePlane(Vec4 _Plane)
{
    // ����� �������� �̿��� ��ü �ʿ� ����Ǵ� ��� ����
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*m_Physics, physx::PxPlane(_Plane.x, _Plane.y, _Plane.z, _Plane.w), *m_Material);
    m_Scene->addActor(*groundPlane);
    return groundPlane;
}

void CPhysXMgr::AddDynamicActor(CRigidbody* _pRigidbody)
{
    m_vecDynamicObject.push_back(_pRigidbody->GetOwner());
    m_vecDynamicActor.push_back(_pRigidbody->m_PxRigidbody);
    m_Scene->addActor(*(_pRigidbody->m_PxRigidbody));
}

void CPhysXMgr::Clear()
{
    // Level �ʱ�ȭ�� ȣ��� ��ü ������ �ʱ�ȭ

    if(!m_vecDynamicActor.empty())
    {
        for (size_t i = 0; i < m_vecDynamicActor.size(); ++i)
        {
            if (nullptr != m_vecDynamicActor[i])
            {
                m_Scene->removeActor(*m_vecDynamicActor[i]);
                m_vecDynamicActor[i]->release();
            }
        }
    }

    if (!m_vecStaticActor.empty())
    {
        for (size_t i = 0; i < m_vecStaticActor.size(); ++i)
        {
            if (nullptr != m_vecStaticActor[i])
            {
                m_Scene->removeActor(*m_vecStaticActor[i]);
                m_vecStaticActor[i]->release();
            }
        }
    }

    m_vecDynamicActor.clear();
    m_vecStaticActor.clear();
    m_vecDynamicObject.clear();
}

void CPhysXMgr::ChangeLevel(LEVEL_TYPE _tType)
{
    // ���� Ÿ�Կ� �´� ������ �� �ε�
    Ptr<CMeshData> pMeshData = nullptr; 
    switch (_tType)
    {
    case LEVEL_TYPE::CASTLE_FIELD:
        pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Castle_Simple.fbx");
        break;
    case LEVEL_TYPE::CASTLE_BOSS:
        pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Castle_Boss_Simple.fbx");
        break;
    case LEVEL_TYPE::FOREST_FIELD:
        pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Forest_Simple.fbx");
        break;
    case LEVEL_TYPE::ICE_FIELD:
        pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Ice_Simple.fbx");
        break;
    case LEVEL_TYPE::ICE_BOSS:
        pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Ice_Boss_Simple.fbx");
        break;
    case LEVEL_TYPE::HALL:
        pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Hall_Simple.fbx");
        break;
    }

    CGameObject* pMap = pMeshData->Instantiate();
    ConvertStatic(Vec3(0.f, 0.f, 0.f), pMap);
}
