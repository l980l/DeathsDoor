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
    vector<CGameObject*>        m_vecDynamicObject;
    vector<PxRigidDynamic*>     m_vecDynamicActor;

    PxRigidDynamic* TestDynamicActor;


public:
    void init();
    void tick();

public:
    // ���� ��ü ���� �Լ�.
    // t : ��ġ, geometry : ����, velocity : �ӵ�
    // ������ ��ü�� ��ȯ��.
    PxRigidDynamic* CreateDynamic(const PxTransform& t, const PxGeometry& geometry, CGameObject* _Object, const PxVec3& velocity = PxVec3(0));

    // ��� ���� �Լ�
    PxRigidStatic* CreatePlane(Vec4 _Plane);

public:
    PxRigidDynamic* GetTestActor() { return TestDynamicActor; }
};

