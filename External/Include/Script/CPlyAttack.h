#pragma once
#include "CState.h"
class CPlyAttack :
    public CState
{
private:
    UINT    m_iAttackCount;         // ���� ����Ƚ��(�� 3ȸ����)
    float   m_fAttackDelay;
    float   m_fAfterAttack;         // ���ݸ���� ���� �� �ð�
    float   m_fLimitTimeNextAttack; // ���ݸ���� ���� �� Idle�� �ǵ��ư��� �ð�
    float   m_fAttackDir;
    Vec3    m_vAttackDir;
    

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    UINT GetAttackCount() { return m_iAttackCount; }
    void CalcDir();
    void Slash();

    CLONE(CPlyAttack);

public:
    CPlyAttack();
    ~CPlyAttack();
};

