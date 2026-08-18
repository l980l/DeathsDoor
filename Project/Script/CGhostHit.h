#pragma once
#include "CState.h"

class CGhostHit :
    public CState
{
    Vec3 vDir;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGhostHit);

    CGhostHit();
    virtual ~CGhostHit() override;
};
