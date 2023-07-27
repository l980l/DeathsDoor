#pragma once
#include "CState.h"
class CPlyFall :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider3D* _Other);
    virtual void OnOverlap(CCollider3D* _Other);
    virtual void EndOverlap(CCollider3D* _Other);

    CLONE(CPlyFall);

public:
    CPlyFall();
    ~CPlyFall();
};

