#pragma once
#include "CState.h"
class CCrowBossStomp :
    public CState
{
private:
    Vec3    m_Dir;
    float   m_fDistance;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossStomp);

public:
    CCrowBossStomp();
    ~CCrowBossStomp();
};

