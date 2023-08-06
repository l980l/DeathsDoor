#pragma once
#include "CState.h"
class CLurkerDeath :
    public CState
{
private:
    bool    m_bStartPaperBurn;
    float   m_fPaperBurnTime;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerDeath);

public:
    CLurkerDeath();
    ~CLurkerDeath();
};
