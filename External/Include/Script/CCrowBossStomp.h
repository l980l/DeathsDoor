#pragma once
#include "CState.h"
class CCrowBossStomp :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossStomp);

public:
    CCrowBossStomp();
    ~CCrowBossStomp();
};

