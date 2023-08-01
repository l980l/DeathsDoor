#pragma once
#include "CState.h"
class CCrowBossStandingDeath :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossStandingDeath);

public:
    CCrowBossStandingDeath();
    ~CCrowBossStandingDeath();
};

