#pragma once
#include "CState.h"
class CPlyAttack :
    public CState
{
private:
    UINT    m_iAttackCount;         // ���� ����Ƚ��(�� 3ȸ����)
    float   m_fAfterAttack;         // ���ݸ���� ���� �� �ð�
    float   m_fLimitTimeNextAttack; // ���ݸ���� ���� �� Idle�� �ǵ��ư��� �ð�

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyAttack);

public:
    CPlyAttack();
    ~CPlyAttack();
};

