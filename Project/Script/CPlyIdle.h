#pragma once
#include "CState.h"

class CPlyIdle :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;

    CLONE(CPlyIdle);

    CPlyIdle();
    virtual ~CPlyIdle() override;
};
