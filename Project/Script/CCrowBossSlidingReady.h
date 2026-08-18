#pragma once
#include "CState.h"

class CCrowBossSlidingReady :
    public CState
{
    vector<CGameObject*> m_vecHook; // Hook
    CHAINPATERN          m_tChainPatern;
    UINT                 m_iThrowCount;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
    void         ThrowHook();
    void         HookArrive();

    CLONE(CCrowBossSlidingReady);

    CCrowBossSlidingReady();
    virtual ~CCrowBossSlidingReady() override;
};
