#pragma once
#include "CIconScript.h"

class CHPIconScript :
    public CIconScript
{
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void SetHP(int _iCurHP) override;

    CLONE(CHPIconScript);

    CHPIconScript();
    virtual ~CHPIconScript() override;
};
