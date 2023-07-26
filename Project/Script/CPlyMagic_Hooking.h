#pragma once
#include "CState.h"
class CPlyMagic_Hooking :
    public CState
{
private:
    Vec3    m_vHookPos;
    bool    m_bAttack;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;
    void SetHookedPos(Vec3 _vHookedPos) { m_vHookPos = _vHookedPos; }


    CLONE(CPlyMagic_Hooking);

public:
    CPlyMagic_Hooking();
    ~CPlyMagic_Hooking();
};

