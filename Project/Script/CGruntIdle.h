#pragma once
#include "CState.h"

class CGruntIdle :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntIdle);

    CGruntIdle();
    virtual ~CGruntIdle() override;
};
