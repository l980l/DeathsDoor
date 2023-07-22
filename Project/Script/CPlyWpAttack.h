#pragma once
#include "CState.h"
class CPlyWpAttack :
    public CState
{
private:
    UINT    m_iAttackCount;         // ���� ����Ƚ��(�� 3ȸ����)

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void SetAttackCount(UINT _iAttackCount);

    CLONE(CPlyWpAttack);

public:
    CPlyWpAttack();
    ~CPlyWpAttack();
};

