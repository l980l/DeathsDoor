#pragma once
#include "CState.h"
class CLurkerNotify :
    public CState
{
private:
    bool    m_bNotify;

public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    CLONE(CLurkerNotify);

public:
    CLurkerNotify();
    ~CLurkerNotify();
};

