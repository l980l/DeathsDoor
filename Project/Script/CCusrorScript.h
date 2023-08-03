#pragma once
#include <Engine/CScript.h>
class CCusrorScript :
    public CScript
{
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CCusrorScript);

    CCusrorScript();
    ~CCusrorScript();
};

