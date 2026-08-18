#pragma once
#include "CState.h"

class CPlyWpMagic_Hook :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpMagic_Hook);

    CPlyWpMagic_Hook();
    virtual ~CPlyWpMagic_Hook() override;
};
