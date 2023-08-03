#pragma once
#include <Engine/CScript.h>
class CHPIconScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CHPIconScript);

public:
    CHPIconScript();
    ~CHPIconScript();
};

