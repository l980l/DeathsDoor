#pragma once
#include "CState.h"

class CKnightJumpAttack2 :
    public CState
{
    float m_fDelay;
    bool  m_bAttack;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightJumpAttack2);

    CKnightJumpAttack2();
    virtual ~CKnightJumpAttack2() override;
};
