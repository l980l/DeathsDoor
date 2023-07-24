#pragma once
#include "CState.h"
class CCrowBossJump :
    public CState
{
private:
    Vec3   m_Dir;
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossJump);

public:
    CCrowBossJump();
    ~CCrowBossJump();
};

