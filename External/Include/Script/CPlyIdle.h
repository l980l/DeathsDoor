#pragma once
#include "CState.h"
class CPlyIdle :
    public CState
{
private:
    bool    m_bWalk;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);

    CLONE(CPlyIdle);

public:
    CPlyIdle();
    ~CPlyIdle();
};

