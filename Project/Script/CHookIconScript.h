#pragma once
#include "CIconScript.h"

class CHookIconScript :
    public CIconScript
{
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void MagicActive(bool _bActive) override;

    CLONE(CHookIconScript);

    CHookIconScript();
    virtual ~CHookIconScript() override;
};
