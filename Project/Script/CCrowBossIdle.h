#pragma once
#include "CState.h"

class CCrowBossIdle :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossIdle);

    CCrowBossIdle();
    virtual ~CCrowBossIdle() override;
};
