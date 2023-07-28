#pragma once
#include "CState.h"
class CPlyMagic_Hook :
    public CState
{
private:
    CGameObject* m_pHook;
    vector<CGameObject*> m_vecChain;
    Vec3    m_vAttackDir;
    bool    m_bHooked;
    bool    m_bHookFail;
    Vec3    m_vHookPos;
    bool    m_bThrow;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;
    void Snatch(Vec3 _vHookedPos) { m_bHooked = true; m_vHookPos = _vHookedPos; }
    void FailSnatch() { m_bHookFail = true; }

    void CalcDir();


    CLONE(CPlyMagic_Hook);

public:
    CPlyMagic_Hook();
    ~CPlyMagic_Hook();
};

