#pragma once
#include "CState.h"
class CPlyWpDance :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpDance);

public:
    CPlyWpDance();
    ~CPlyWpDance();
};

