#pragma once
#include "CState.h"
class CPlyChargeAttack :
    public CState
{
private:
          

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    CLONE(CPlyChargeAttack);

public:
    CPlyChargeAttack();
    ~CPlyChargeAttack();
};

