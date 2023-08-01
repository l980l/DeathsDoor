#pragma once
#include "CState.h"
class CGruntDeath :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntDeath);

public:
    CGruntDeath();
    ~CGruntDeath();
};

