#pragma once
#include <Engine/CScript.h>
class CMoneyCountScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CMoneyCountScript);

public:
    CMoneyCountScript();
    ~CMoneyCountScript();
};
