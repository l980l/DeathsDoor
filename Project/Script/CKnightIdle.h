#pragma once
#include "CState.h"
class CKnightIdle :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightIdle);

public:
    CKnightIdle();
    ~CKnightIdle();
};

