#pragma once
#include "CComponent.h"

class CRigidbody :
    public CComponent
{
private:
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
    void AddForce(Vec3 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }

    float GetVelocityLimit() { return m_fVelocityLimit; }
    float GetGravityLimit() { return m_fGravityVLimit; }

    void SetVelocity(Vec3 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec3 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vec3 _vAddV) { m_vVelocity += _vAddV; }

    void SetMass(float _fMass) { m_fMass = _fMass; }
    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }
    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
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

