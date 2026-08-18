#pragma once
#include "CState.h"

class CPlyDance :
    public CState
{
    float m_fCameraZoomIn;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyDance);

    CPlyDance();
    virtual ~CPlyDance() override;
};
