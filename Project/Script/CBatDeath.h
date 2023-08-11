#pragma once
#include "CState.h"
class CBatDeath :
    public CState
{
private:
    bool            m_bStartPaperBurn;
    float            m_fPaperBurnTime;
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CBatDeath);

public:
    CBatDeath();
    ~CBatDeath();
};

