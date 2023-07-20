#pragma once
#include "CState.h"
class CPlyWpAttack :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpAttack);

public:
    CPlyWpAttack();
    ~CPlyWpAttack();
};

