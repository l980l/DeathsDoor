#pragma once
#include "CState.h"
class CBazzokaMove :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CBazzokaMove);

public:
    CBazzokaMove();
    ~CBazzokaMove();
};