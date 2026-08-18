#pragma once
#include "CState.h"

class CSpeed :
    public CState
{
    bool m_bCheck;

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    bool GetSpeedCheck() const { return m_bCheck; }
    void SetSpeedCheck(bool _check) { m_bCheck = _check; }
    CLONE(CSpeed);

    CSpeed();
    virtual ~CSpeed() override;
};
