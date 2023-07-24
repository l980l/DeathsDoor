#pragma once
#include "CState.h"
class CPlyMagic_Hook :
    public CState
{
    float m_fMagicChargeTime;
    Vec3  m_vAttackDir;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    void CalcDir();

    CLONE(CPlyMagic_Hook);

public:
    CPlyMagic_Hook();
    ~CPlyMagic_Hook();
};

