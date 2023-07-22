#pragma once
#include "CState.h"
class CPlyRun :
    public CState
{
private:
    float   m_fSpeed; 
    float   m_fTimeToIdle;
    bool    m_bIce;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void Move();
    void CalcDir();

    CLONE(CPlyRun);

public:
    CPlyRun();
    ~CPlyRun();
};

