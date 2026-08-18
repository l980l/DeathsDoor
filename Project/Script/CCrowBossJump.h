#pragma once
#include "CState.h"

class CCrowBossJump :
    public CState
{
    float m_fDistance;
    Vec3  m_Dir;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossJump);

    CCrowBossJump();
    virtual ~CCrowBossJump() override;
};
