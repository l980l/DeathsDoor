#pragma once
#include <Engine/CScript.h>
class CArrowIconScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CArrowIconScript);

public:
    CArrowIconScript();
    ~CArrowIconScript();
};

