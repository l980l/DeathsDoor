#pragma once
#include "CState.h"
class CLurkerBackStep :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerBackStep);

public:
    CLurkerBackStep();
    ~CLurkerBackStep();
};

