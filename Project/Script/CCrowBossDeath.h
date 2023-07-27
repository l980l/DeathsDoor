#pragma once
#include "CState.h"
class CCrowBossDeath :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossDeath);

public:
    CCrowBossDeath();
    ~CCrowBossDeath();
};

