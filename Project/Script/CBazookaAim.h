#pragma once
#include "CState.h"

class CBazookaAim :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CBazookaAim);

    CBazookaAim();
    virtual ~CBazookaAim() override;
};
