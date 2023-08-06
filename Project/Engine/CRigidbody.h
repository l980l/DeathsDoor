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

    void AddForce(Vec3 _vForce);
    void ClearForce();

    void AddVelocity(Vec3 _vVelocity);
    void SetVelocity(Vec3 _vVelocity);
    void SetVelocityLimit(float _fLimit);
    void SetGravity(float _fGravity);
    Vec3 GetVelocity();
    void SetMass(float _fMass);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CRigidbody);

public:
    CRigidbody();
    ~CRigidbody();
};

