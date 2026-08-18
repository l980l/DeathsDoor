#pragma once
#include "CState.h"

class CPlyWpMagic_Bomb :
    public CState
{
    float m_fChargeDelay;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpMagic_Bomb);

    CPlyWpMagic_Bomb();
    virtual ~CPlyWpMagic_Bomb() override;
};
