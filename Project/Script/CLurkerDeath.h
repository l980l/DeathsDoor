#pragma once
#include "CState.h"

class CLurkerDeath :
    public CState
{
    bool  m_bStartPaperBurn;
    float m_fPaperBurnTime;
    float m_fTime;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerDeath);

    CLurkerDeath();
    virtual ~CLurkerDeath() override;
};
