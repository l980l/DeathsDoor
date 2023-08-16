#pragma once
#include "CState.h"
class CKnightWalk :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightWalk);

public:
    CKnightWalk();
    ~CKnightWalk();
};

