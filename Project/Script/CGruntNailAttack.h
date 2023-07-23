#pragma once
#include "CState.h"
class CGruntNailAttack :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntNailAttack);

public:
    CGruntNailAttack();
    ~CGruntNailAttack();
};

