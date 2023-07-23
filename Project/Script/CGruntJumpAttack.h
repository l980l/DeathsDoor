#pragma once
#include "CState.h"
class CGruntJumpAttack :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntJumpAttack);

public:
    CGruntJumpAttack();
    ~CGruntJumpAttack();
};

