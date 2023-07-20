#pragma once
#include "CState.h"
class CBazookaAim :
    public CState
{
private:
    float   m_fAimTime;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CBazookaAim);

public:
    CBazookaAim();
    ~CBazookaAim();
};

