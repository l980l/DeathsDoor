#pragma once
#include "CState.h"

class CLurkerBackMove :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerBackMove);

    CLurkerBackMove();
    virtual ~CLurkerBackMove() override;
};
