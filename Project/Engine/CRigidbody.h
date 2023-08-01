#pragma once
#include "CComponent.h"
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>

class PxRigidDynamic;

class CRigidbody :
    public CComponent
{
private:
    physx::PxRigidDynamic* m_PxRigidbody;

public:
    virtual void finaltick() override {};
    
    void SetGround(bool _bOn) {};
    void SetFriction(float _fFriction) {};
    void SetFrictionScale(float _fFrictionScale) {};

public:
    void SetRigidbody(void* _pRigidbody);
    void SetAngularVelocity(Vec3 _vAngvel)
    {
        const physx::PxVec3& Angvel = physx::PxVec3(_vAngvel.x, _vAngvel.y, _vAngvel.z);
        m_PxRigidbody->setAngularVelocity(Angvel);
    }
    void AddTorque(Vec3 _vTorque)
    {
        const physx::PxVec3& Torque = physx::PxVec3(_vTorque.x, _vTorque.y, _vTorque.z);
        m_PxRigidbody->addTorque(Torque);
    }
    void AddForce(Vec3 _vForce) 
    {
        const physx::PxVec3& Force =  physx::PxVec3(_vForce.x, _vForce.y, _vForce.z);
        m_PxRigidbody->addForce(Force, physx::PxForceMode::eFORCE);
    }
    void SetVelocityLimit(float _fLimit) {m_PxRigidbody->setMaxLinearVelocity(physx::PxReal(_fLimit));}
    void AddVelocity(Vec3 _vVelocity)
    {
        physx::PxVec3 AddVelocity = physx::PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
        physx::PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
        m_PxRigidbody->setLinearVelocity(AddVelocity + LinearVelocity);
    }
    void SetVelocity(Vec3 _vVelocity) 
    { 
        const physx::PxVec3& Velocity = physx::PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
        m_PxRigidbody->setLinearVelocity(Velocity);
    }
    Vec3 GetVelocity() 
    { 
        physx::PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
        return Vec3(LinearVelocity.x, LinearVelocity.y, LinearVelocity.z);
    }

    void SetMass(float _fMass) {m_PxRigidbody->setMass(physx::PxReal(_fMass));}

    virtual void SaveToLevelFile(FILE* _File) {};
    virtual void LoadFromLevelFile(FILE* _FILE) {};

    CLONE(CRigidbody);

public:
    CRigidbody();
    ~CRigidbody();
};

