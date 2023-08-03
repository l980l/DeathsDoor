#pragma once
#include <Engine/CScript.h>
class CBombIconScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CBombIconScript);

public:
    CBombIconScript();
    ~CBombIconScript();
};

