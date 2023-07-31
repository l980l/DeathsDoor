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
    Vec3    m_vForce;           // 힘
    Vec3    m_vVelocity;        // 속도 ( vector )
    float   m_fMass;            // 질량

    float   m_fFriction;        // 마찰력
    float   m_fFrictionScale;   // 마찰계수

    float   m_fVelocityLimit;   // 제한 속도
    float   m_fGravityVLimit;   // 중력에 의한 제한 속도


    float   m_fGravityAccel;    // 중력 가속도 설정
    bool    m_bGravityUse;      // 중력 사용여부
    bool    m_bGround;          // 땅 체크
    bool    m_bIce;             // *얼음 위 체크

public:
    virtual void finaltick() override;
    
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
    void SetVelocityLimit(float _fLimit) { 

        m_PxRigidbody->setMaxLinearVelocity(physx::PxReal(_fLimit));
        m_fVelocityLimit = _fLimit; }

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

    void SetMass(float _fMass) {
        m_PxRigidbody->setMass(physx::PxReal(_fMass));
    }
    void SetFriction(float _fFriction) 
    { 
        m_fFriction = _fFriction;
    }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }
    void SetGround(bool _bGround);
    void SetIce(bool _bIce);

    float GetMass() { return m_fMass; }
    float GetFriction() { return m_fFriction; }
    float GetFrictionScale() { return m_fFrictionScale; }    
    bool IsUseGravity() { return m_bGravityUse; }
    bool GetGravityAccel() { return m_fGravityAccel; }
    bool IsGround() { return m_bGround; }
    bool IsIce() { return m_bIce; }

public:
    virtual void SaveToLevelFile(FILE* _pFile) override;
    virtual void LoadFromLevelFile(FILE* _pFile) override;
    CLONE(CRigidbody);

public:
    CRigidbody();
    ~CRigidbody();
};

