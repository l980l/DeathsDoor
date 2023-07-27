#pragma once
#include "CState.h"
class CPlyDance :
    public CState
{
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyDance);

public:
    CPlyDance();
    ~CPlyDance();
};

