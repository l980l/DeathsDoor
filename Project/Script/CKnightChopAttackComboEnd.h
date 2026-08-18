#pragma once
#include "CState.h"

class CKnightChopAttackComboEnd :
    public CState
{
    float m_fTime;
    bool  m_bCameraShake;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightChopAttackComboEnd);

    CKnightChopAttackComboEnd();
    virtual ~CKnightChopAttackComboEnd() override;
};
