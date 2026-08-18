#pragma once
#include "CState.h"

class CGrimKnightBackStep :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGrimKnightBackStep);

    CGrimKnightBackStep();
    virtual ~CGrimKnightBackStep() override;
};
