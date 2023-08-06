#pragma once
#include <Engine/CScript.h>
class CHookIconScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CHookIconScript);

public:
    CHookIconScript();
    ~CHookIconScript();
};

