#pragma once
#include "CState.h"

class CCrowBossDeath :
    public CState
{
    bool  m_bStartPaperBurn;
    float m_fPaperBurnTime;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossDeath);

    CCrowBossDeath();
    virtual ~CCrowBossDeath() override;
};
