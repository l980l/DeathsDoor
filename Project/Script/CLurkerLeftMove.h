#pragma once
#include "CState.h"

class CLurkerLeftMove :
    public CState
{
    float m_fTime;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerLeftMove);

    CLurkerLeftMove();
    virtual ~CLurkerLeftMove() override;
};
