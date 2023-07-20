#pragma once
#include "CState.h"
class CBazookaDeath :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CBazookaDeath);

public:
    CBazookaDeath();
    ~CBazookaDeath();
};

