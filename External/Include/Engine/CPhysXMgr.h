#pragma once
#include "CSingleton.h"
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>
#include "CGameObject.h"

// PhysX Library
#pragma comment(lib, "PhysX//PhysX_64")
#pragma comment(lib, "PhysX//PhysXCommon_64")
#pragma comment(lib, "PhysX//PhysXFoundation_64")

#pragma comment(lib, "PhysX//LowLevel_static_64")
#pragma comment(lib, "PhysX//LowLevelAABB_static_64")
#pragma comment(lib, "PhysX//LowLevelDynamics_static_64")
#pragma comment(lib, "PhysX//PhysXCharacterKinematic_static_64")
#pragma comment(lib, "PhysX//PhysXCooking_64")
#pragma comment(lib, "PhysX//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//PhysXPvdSDK_static_64")
#pragma comment(lib, "PhysX//PhysXTask_static_64")
#pragma comment(lib, "PhysX//PhysXVehicle_static_64")
#pragma comment(lib, "PhysX//SceneQuery_static_64")

using namespace physx;

class CPhysXMgr :
    public CSingleton<CPhysXMgr>
{
    SINGLE(CPhysXMgr);

private:
    // 변수 선언
    physx::PxDefaultErrorCallback       m_DefaultErrorCallback;
    physx::PxDefaultAllocator           m_DefaultAllocatorCallback;
    physx::PxDefaultCpuDispatcher*      m_Dispatcher = NULL;
    physx::PxTolerancesScale            m_ToleranceScale;

    physx::PxFoundation*                m_Foundation = NULL;
    physx::PxPhysics*                   m_Physics = NULL;

    physx::PxScene*                     m_Scene = NULL;
    physx::PxMaterial*                  m_Material = NULL;

    physx::PxPvd*                       m_Pvd = NULL;
    physx::PxCooking*                   m_Cooking = NULL;
    physx::PxPvdTransport*              m_Transport = NULL;

    vector<CGameObject*>                m_vecDynamicObject;
    vector<physx::PxRigidDynamic*>      m_vecDynamicActor;
    vector<physx::PxRigidStatic*>       m_vecStaticActor;
    float                               m_fUpdateTime;

public:
    void init();
    void tick();
    void finaltick();

private:
    physx::PxRigidDynamic* CreateDynamic(Vec3 _vSpawnPos, const PxGeometry& geometry, CGameObject* _Object, float _fYOffset,  const PxVec3& velocity = PxVec3(0));

public:
    // 동적 물체 생성 함수.
    // t : 위치, geometry : 형태, velocity : 속도
    // 생성된 물체를 반환함.
    physx::PxRigidDynamic* CreateCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object, Vec3 _vVelocity = Vec3(0.f));
    physx::PxRigidDynamic* CreateCapsule(Vec3 _vSpawnPos, float _fRadius, float _fHeight, CGameObject* _Object, Vec3 _vVelocity = Vec3(0.f));
    physx::PxRigidDynamic* CreateSphere(Vec3 _vSpawnPos, float _fRadius, CGameObject* _Object, Vec3 _vVelocity = Vec3(0.f));
    physx::PxRigidStatic* ConvertStatic(Vec3 _vSpawnPos, CGameObject* _Object);
    physx::PxRigidStatic* CreateStaticCube(Vec3 _vSpawnPos, Vec3 _vCubeScale, CGameObject* _Object);

    void SetRigidPos(physx::PxRigidDynamic* _pDynamic, Vec3 _vPos);
    void ReleaseStatic(physx::PxRigidStatic* _pStatic);
    void ReleaseDynamic(physx::PxRigidDynamic* _pDynamic, CGameObject* _pObject);
    // 평면 생성 함수
    physx::PxRigidStatic* CreatePlane(Vec4 _Plane);
    void AddDynamicActor(CRigidbody* _pRigidbody);
    void Clear();
    void ChangeLevel(LEVEL_TYPE _tType);

};
