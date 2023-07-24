#pragma once
#include "CState.h"
class CCrowBossSlidingReady :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossSlidingReady);

public:
    CCrowBossSlidingReady();
    ~CCrowBossSlidingReady();
};

