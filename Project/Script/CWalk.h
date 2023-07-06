#pragma once
#include "CState.h"
class CWalk :
    public CState
{
private:
    float   m_fSpeed;
    float   m_fTimeToIdle;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void Move();

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CWalk);

public:
    CWalk();
    ~CWalk();
};

