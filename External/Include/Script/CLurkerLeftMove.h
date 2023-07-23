#pragma once
#include "CState.h"
class CLurkerLeftMove :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerLeftMove);

public:
    CLurkerLeftMove();
    ~CLurkerLeftMove();
};

