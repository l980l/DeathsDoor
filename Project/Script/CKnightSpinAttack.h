#pragma once
#include "CState.h"

class CKnightSpinAttack :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightSpinAttack);

    CKnightSpinAttack();
    virtual ~CKnightSpinAttack() override;
};
