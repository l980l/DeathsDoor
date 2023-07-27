#pragma once
#include "CState.h"
class CLurkerDeath :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerDeath);

public:
    CLurkerDeath();
    ~CLurkerDeath();
};

