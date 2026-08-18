#pragma once
#include "CState.h"

class CPlyWpLadder :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpLadder);

    CPlyWpLadder();
    virtual ~CPlyWpLadder() override;
};
