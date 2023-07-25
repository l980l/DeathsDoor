#pragma once
#include "CState.h"
class CPlyWpMagic_Hook :
    public CState
{
private:
    float m_fChargeDelay;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpMagic_Hook);

public:
    CPlyWpMagic_Hook();
    ~CPlyWpMagic_Hook();
};

