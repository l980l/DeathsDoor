#pragma once
#include "CState.h"
class CBatRecognize :
    public CState
{
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CBatRecognize);

public:
    CBatRecognize();
    ~CBatRecognize();
};

