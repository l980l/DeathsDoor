#pragma once
#include "CState.h"
class CPlyMagic_Hook :
    public CState
{
    float   m_fMagicChargeTime;
    Vec3    m_vAttackDir;
    bool    m_bHooked;
    Vec3    m_vHookPos;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;
    void Snatch(Vec3 _vHookedPos) { m_bHooked = true; m_vHookPos = _vHookedPos; }

    void CalcDir();

    CLONE(CPlyMagic_Hook);

public:
    CPlyMagic_Hook();
    ~CPlyMagic_Hook();
};

