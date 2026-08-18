#pragma once
#include "CState.h"

class CGrimKnightGuard :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGrimKnightGuard);

    CGrimKnightGuard();
    virtual ~CGrimKnightGuard() override;
};
