#pragma once
#include "CState.h"
class CPlyCharge :
    public CState
{
private:
    float m_fMaxChargeTime;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyCharge);

public:
    CPlyCharge();
    ~CPlyCharge();
};

