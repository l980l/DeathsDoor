#pragma once
#include "CState.h"
class CSpeed :
    public CState
{
private:
    bool b_check;
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    bool GetSpeedCheck() { return b_check; }
    void SetSpeedCheck(bool _check) { b_check = _check; }
    CLONE(CSpeed);

public:
    CSpeed();
    ~CSpeed();
};

