#pragma once
#include "CState.h"
class CKnightRunAttack :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightRunAttack);

public:
    CKnightRunAttack();
    ~CKnightRunAttack();
};

