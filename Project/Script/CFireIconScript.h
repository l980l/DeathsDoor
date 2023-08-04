#pragma once
#include <Engine/CScript.h>
class CFireIconScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CFireIconScript);

public:
    CFireIconScript();
    ~CFireIconScript();
};

