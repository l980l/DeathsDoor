#pragma once
#include "CState.h"
class CGrimKnightBackStep2 :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CGrimKnightBackStep2);

public:
    CGrimKnightBackStep2();
    ~CGrimKnightBackStep2();
};

