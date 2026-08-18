#pragma once
#include "CIconScript.h"

class CBombIconScript :
    public CIconScript
{
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void MagicActive(bool _bActive) override;

    CLONE(CBombIconScript);

    CBombIconScript();
    virtual ~CBombIconScript() override;
};
