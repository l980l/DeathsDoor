#pragma once
#include "CState.h"

class CPlyFall :
    public CState
{
    float m_fTimeToIdle;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CPlyFall);

    CPlyFall();
    virtual ~CPlyFall() override;
};
