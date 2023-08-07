#pragma once
#include <Engine\CScript.h>
class CWaterScript :
    public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CWaterScript);

public:
    CWaterScript();
    ~CWaterScript();
};

