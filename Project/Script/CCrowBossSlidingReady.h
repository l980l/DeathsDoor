#pragma once
#include "CState.h"
class CCrowBossSlidingReady :
    public CState
{
private:
    vector<CGameObject*>    m_vecHook;          // Hook
    vector<Vec3>            m_vecThrowPos;      // ���� ���� ���� ��� �������ϴ� ��ġ
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

