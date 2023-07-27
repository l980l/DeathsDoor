#pragma once
#include "CState.h"
class CBazzokaMove :
    public CState
{
private:
    float m_fLastRenewal;
    float m_fRenewal_Trace; // ���� ��θ� �����ϴ� �ֱ�
    Vec3  m_vActualPath[256];
    int   m_iActualPathCount;
    int   m_iCurrentPathIndex;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CBazzokaMove);

public:
    CBazzokaMove();
    ~CBazzokaMove();
};