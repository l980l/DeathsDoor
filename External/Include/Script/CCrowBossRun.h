#pragma once
#include "CState.h"
class CCrowBossRun :
    public CState
{
private:
    int     m_iTime;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossRun);

public:
    CCrowBossRun();
    ~CCrowBossRun();
};

