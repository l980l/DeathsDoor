#pragma once
#include "CState.h"

class CBatDeath :
    public CState
{
    float m_fPaperBurnTime;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CBatDeath);

    CBatDeath();
    virtual ~CBatDeath() override;
};
