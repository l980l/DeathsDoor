#pragma once
#include "CState.h"
class CGruntRun2 :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntRun2);

public:
    CGruntRun2();
    ~CGruntRun2();
};

