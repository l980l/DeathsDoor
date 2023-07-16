#pragma once
#include "CState.h"
class CTrace :
    public CState
{
private:
    float m_fLastRenewal;
    float m_fRenewal_Trace; // ���� ��θ� �����ϴ� �ֱ�

    Vec3  m_vActualPath[256];
    int   m_iactualPathCount;
    int   m_icurrentPathIndex;

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

