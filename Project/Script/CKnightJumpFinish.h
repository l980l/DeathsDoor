#pragma once
#include "CState.h"

class CKnightJumpFinish :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightJumpFinish);

    CKnightJumpFinish();
    virtual ~CKnightJumpFinish() override;
};
