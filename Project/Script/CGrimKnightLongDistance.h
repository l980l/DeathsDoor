#pragma once
#include "CState.h"
class CGrimKnightLongDistance :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CGrimKnightLongDistance);

public:
    CGrimKnightLongDistance();
    ~CGrimKnightLongDistance();
};

