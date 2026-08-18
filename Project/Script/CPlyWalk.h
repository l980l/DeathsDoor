#pragma once
#include "CState.h"

class CPlyWalk :
    public CState
{
    float m_fSpeed;
    float m_fTimeToIdle;
    bool  m_bIce;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void Move();

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CPlyWalk);

    CPlyWalk();
    virtual ~CPlyWalk() override;
};
