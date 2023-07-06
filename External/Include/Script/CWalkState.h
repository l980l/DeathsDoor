#pragma once
#include "CState.h"
class CWalkState :
    public CState
{
private:
    float   m_fSpeed;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CWalkState);

public:
    CWalkState();
    ~CWalkState();
};

