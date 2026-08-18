#pragma once
#include "CState.h"

class CAttackSpeed :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CAttackSpeed);

    CAttackSpeed();
    virtual ~CAttackSpeed() override;
};
