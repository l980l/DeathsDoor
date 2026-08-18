#pragma once
#include "CState.h"

class CGruntRightMove :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntRightMove);

    CGruntRightMove();
    virtual ~CGruntRightMove() override;
};
