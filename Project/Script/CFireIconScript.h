#pragma once
#include "CIconScript.h"

class CFireIconScript :
    public CIconScript
{
public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void MagicActive(bool _bActive) override;

    CLONE(CFireIconScript);

    CFireIconScript();
    virtual ~CFireIconScript() override;
};
