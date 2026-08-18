#pragma once
#include "CState.h"

class CPlyWpMagic_Fire :
    public CState
{
    float m_fChargeDelay;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpMagic_Fire);

    CPlyWpMagic_Fire();
    virtual ~CPlyWpMagic_Fire() override;
};
