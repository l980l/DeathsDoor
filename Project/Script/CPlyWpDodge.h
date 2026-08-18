#pragma once
#include "CState.h"

class CPlyWpDodge :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpDodge);

    CPlyWpDodge();
    virtual ~CPlyWpDodge() override;
};
