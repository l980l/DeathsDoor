#pragma once
#include "CState.h"
class CPlyAttack_Magic :
    public CState
{
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CPlyAttack_Magic);

public:
    CPlyAttack_Magic();
    ~CPlyAttack_Magic();
};

