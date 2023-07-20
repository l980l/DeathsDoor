#pragma once
#include "CState.h"
class CPlyWpMagic :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpMagic);

public:
    CPlyWpMagic();
    ~CPlyWpMagic();
};

