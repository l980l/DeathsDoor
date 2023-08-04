#pragma once
#include <Engine/CScript.h>
class CEnergyIconScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CEnergyIconScript);

public:
    CEnergyIconScript();
    ~CEnergyIconScript();
};

