#pragma once
#include "CSingleton.h"
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>
#include "CGameObject.h"

// PhysX Library
#ifdef _DEBUG
#pragma comment(lib, "PhysX//debug//PhysX_64")
#pragma comment(lib, "PhysX//debug//PhysXCommon_64")
#pragma comment(lib, "PhysX//debug//PhysXFoundation_64")

#pragma comment(lib, "PhysX//debug//LowLevel_static_64")
#pragma comment(lib, "PhysX//debug//LowLevelAABB_static_64")
#pragma comment(lib, "PhysX//debug//LowLevelDynamics_static_64")
#pragma comment(lib, "PhysX//debug//PhysXCharacterKinematic_static_64")
#pragma comment(lib, "PhysX//debug//PhysXCooking_64")
#pragma comment(lib, "PhysX//debug//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//debug//PhysXPvdSDK_static_64")
#pragma comment(lib, "PhysX//debug//PhysXTask_static_64")
#pragma comment(lib, "PhysX//debug//PhysXVehicle_static_64")
#pragma comment(lib, "PhysX//debug//SceneQuery_static_64")
#else
#pragma comment(lib, "PhysX//release//PhysX_64")
#pragma comment(lib, "PhysX//release//PhysXCommon_64")
#pragma comment(lib, "PhysX//release//PhysXFoundation_64")

#pragma comment(lib, "PhysX//release//LowLevel_static_64")
#pragma comment(lib, "PhysX//release//LowLevelAABB_static_64")
#pragma comment(lib, "PhysX//release//LowLevelDynamics_static_64")
#pragma comment(lib, "PhysX//release//PhysXCharacterKinematic_static_64")
#pragma comment(lib, "PhysX//release//PhysXCooking_64")
#pragma comment(lib, "PhysX//release//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//release//PhysXPvdSDK_static_64")
#pragma comment(lib, "PhysX//release//PhysXTask_static_64")
#pragma comment(lib, "PhysX//release//PhysXVehicle_static_64")
#pragma comment(lib, "PhysX//release//SceneQuery_static_64")
#endif

using namespace physx;

class CPhysXMgr :
    public CSingleton<CPhysXMgr>
{
    SINGLE(CPhysXMgr);

    // 변수 선언
    PxDefaultErrorCallback  m_DefaultErrorCallback;
    PxDefaultAllocator      m_DefaultAllocatorCallback;
    PxDefaultCpuDispatcher* m_Dispatcher = nullptr;
    PxTolerancesScale       m_ToleranceScale;

    PxFoundation* m_Foundation = nullptr;
    PxPhysics*    m_Physics    = nullptr;

    PxScene*    m_Scene    = nullptr;
    PxMaterial* m_Material = nullptr;

    PxPvd*          m_Pvd       = nullptr;
    PxCooking*      m_Cooking   = nullptr;
    PxPvdTransport* m_Transport = nullptr;

    vector<CGameObject*>    m_vecDynamicObject;
    vector<PxRigidDynamic*> m_vecDynamicActor;
    vector<PxRigidStatic*>  m_vecStaticActor;

    float m_fFecthDelay;

public:
    void init();
    void tick() const;
    void finaltick();

private:
    PxRigidDynamic* CreateDynamic(Vec3 _vSpawnPos, const PxGeometry& geometry, CGameObject* _Object, float _fYOffset, const PxVec3& velocity = PxVec3(0));
    void            SetRigidPos(PxRigidDynamic* _pDynamic, Vec3 _vPos) const;

public:
    // 동적 물체 생성 함수.
    // t : 위치, geometry : 형태, velocity : 속도
    // 생성된 물체를 반환함.
    PxRigidDynamic* CreateCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object, Vec3 _vVelocity = Vec3(0.f));
    PxRigidDynamic* CreateCapsule(Vec3 _vSpawnPos, float _fRadius, float _fHeight, CGameObject* _Object, Vec3 _vVelocity = Vec3(0.f));
    PxRigidDynamic* CreateSphere(Vec3 _vSpawnPos, float _fRadius, CGameObject* _Object, Vec3 _vVelocity = Vec3(0.f));
    PxRigidStatic*  ConvertStatic(Vec3 _vSpawnPos, CGameObject* _Object);
    PxRigidStatic*  CreateStaticCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object);

    void ReleaseStatic(PxRigidStatic* _pStatic);
    void ReleaseDynamic(PxRigidDynamic* _pDynamic, CGameObject* _pObject);

    // 평면 생성 함수
    PxRigidStatic* CreatePlane(Vec4 _Plane);
    void           AddDynamicActor(CRigidbody* _pRigidbody);
    void           Clear();
    void           ChangeLevel(LEVEL_TYPE _tType);

    friend class CRigidbody;
};
