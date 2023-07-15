#pragma once
#include "CComponent.h"

class CRigidbody :
    public CComponent
{
private:
    Vec3    m_vForce;           // ��
    Vec3    m_vVelocity;        // �ӵ� ( vector )
    float   m_fMass;            // ����

    float   m_fFriction;        // ������
    float   m_fFrictionScale;   // �������

    float   m_fVelocityLimit;   // ���� �ӵ�
    float   m_fGravityVLimit;   // �߷¿� ���� ���� �ӵ�


    float   m_fGravityAccel;    // �߷� ���ӵ� ����
    bool    m_bGravityUse;      // �߷� ��뿩��
    bool    m_bGround;          // �� üũ
    bool    m_bIce;             // *���� �� üũ

public:
    virtual void finaltick() override;

public:
    void AddForce(Vec3 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }

    void SetVelocity(Vec3 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec3 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vec3 _vAddV) { m_vVelocity += _vAddV; }

    void SetFriction(float _f) { m_fFriction = _f; }
    void SetFrictionScale(float _f) { m_fFrictionScale = _f; }
    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }
    void SetGround(bool _bGround);

public:
    virtual void SaveToLevelFile(FILE* _pFile) override;
    virtual void LoadFromLevelFile(FILE* _pFile) override;
    CLONE(CRigidbody);

public:
    CRigidbody();
    ~CRigidbody();
};

