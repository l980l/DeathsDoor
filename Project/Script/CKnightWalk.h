#pragma once
#include "CState.h"

class CKnightWalk :
    public CState
{
    float m_fWalkSoundDelay;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CKnightWalk);

    CKnightWalk();
    virtual ~CKnightWalk() override;
};
