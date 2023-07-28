#pragma once
#include "CState.h"
class CPlyAttack :
    public CState
{
private:
    UINT    m_iAttackCount;         // 현재 공격횟수(총 3회까지)
    float   m_fAttackDelay;
    float   m_fAfterAttack;         // 공격모션이 끝난 후 시간
    float   m_fLimitTimeNextAttack; // 공격모션이 끝난 후 Idle로 되돌아가는 시간
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

