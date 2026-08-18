#pragma once
#include "CState.h"

class CKnightDeath :
    public CState
{
    bool  m_bStartPaperBurn;
    float m_fPaperBurnTime;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightDeath);

    CKnightDeath();
    virtual ~CKnightDeath() override;
};
