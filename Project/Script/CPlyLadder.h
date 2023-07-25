#pragma once
#include "CState.h"
class CPlyLadder :
    public CState
{
private:
    float m_fSpeed;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    void Move();

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CPlyLadder);

public:
    CPlyLadder();
    ~CPlyLadder();
};

