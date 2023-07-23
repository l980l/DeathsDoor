#pragma once
#include "CState.h"
class CPlyMagic_Fire :
    public CState
{
    float m_fMagicChargeTime;
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CPlyMagic_Fire);

public:
    CPlyMagic_Fire();
    ~CPlyMagic_Fire();
};

