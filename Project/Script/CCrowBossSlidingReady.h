#pragma once
#include "CState.h"
class CCrowBossSlidingReady :
    public CState
{
private:
    vector<CGameObject*>    m_vecHook;          // Hook
    vector<Vec3>            m_vecThrowPos;      // 여러 개를 던질 경우 던져야하는 위치
    bool                    m_bThrowmany;
    bool                    m_bThrowReady;
    UINT                    m_iThrowCount;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
    void ThrowHook();
    void HookArrive();
    void SetPatern();

    CLONE(CCrowBossSlidingReady);

public:
    CCrowBossSlidingReady();
    ~CCrowBossSlidingReady();
};

