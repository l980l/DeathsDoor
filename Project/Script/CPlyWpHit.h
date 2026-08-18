#pragma once
#include "CState.h"

class CPlyWpHit :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpHit);

    CPlyWpHit();
    virtual ~CPlyWpHit() override;
};
