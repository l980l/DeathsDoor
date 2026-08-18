#pragma once
#include "CState.h"

class CGruntNailAttack :
    public CState
{
    float m_fTime;
    Vec3  m_Dir;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CGruntNailAttack);

    CGruntNailAttack();
    virtual ~CGruntNailAttack() override;
};
