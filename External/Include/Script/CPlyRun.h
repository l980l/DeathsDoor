#pragma once
#include "CState.h"
class CPlyRun :
    public CState
{
private:
    float   m_fSpeed; 
    float   m_fTimeToIdle;
    float   m_fRotDelay;
    float   m_fRot;
    bool    m_bIce;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void Move();
    void CalcDir();

    virtual void BeginOverlap(CCollider2D* _Other);

    CLONE(CPlyRun);

public:
    CPlyRun();
    ~CPlyRun();
};

