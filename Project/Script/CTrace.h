#pragma once
#include "CState.h"
class CTrace :
    public CState
{
private:
    float m_fLastRenewal;
    float m_fRenewal_Trace; // 추적 경로를 갱신하는 주기
    float m_fSpeed;
    Vec3  m_vActualPath[256];
    int   m_iActualPathCount;
    int   m_iCurrentPathIndex;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CTrace);

public:
    CTrace();
    ~CTrace();
};

