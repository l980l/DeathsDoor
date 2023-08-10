#pragma once
#include "CState.h"
class CCrowBossChainThrow :
    public CState
{
private:
    CGameObject*            m_pHook;
    vector<CGameObject*>    m_vecChain;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossChainThrow);

public:
    CCrowBossChainThrow();
    ~CCrowBossChainThrow();
};

