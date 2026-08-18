#pragma once
#include "CIconScript.h"

class CArrowIconScript :
    public CIconScript
{
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void MagicActive(bool _bActive) override;

    CLONE(CArrowIconScript);

    CArrowIconScript();
    virtual ~CArrowIconScript() override;
};
