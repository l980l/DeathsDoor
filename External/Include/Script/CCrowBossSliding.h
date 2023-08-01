#pragma once
#include "CState.h"
class CCrowBossSliding :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossSliding);

public:
    CCrowBossSliding();
    ~CCrowBossSliding();
};

