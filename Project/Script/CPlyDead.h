#pragma once
#include "CState.h"
class CPlyDead :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyDead);

public:
    CPlyDead();
    ~CPlyDead();
};

