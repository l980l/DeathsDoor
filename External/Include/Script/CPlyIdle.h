#pragma once
#include "CState.h"
class CPlyIdle :
    public CState
{
private:
    bool    m_bWalk;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyIdle);

public:
    CPlyIdle();
    ~CPlyIdle();
};

