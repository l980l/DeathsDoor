#pragma once
#include "CState.h"

class CPlyWpDance :
    public CState
{
    float m_fCameraZoomIn;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CPlyWpDance);

    CPlyWpDance();
    virtual ~CPlyWpDance() override;
};
