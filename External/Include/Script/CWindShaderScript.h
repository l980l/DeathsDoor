#pragma once
#include <Engine\CScript.h>

class CWindShaderScript :
    public CScript
{
private:
    float   m_fTime;
    bool    m_bSpawn;
    Vec4    m_vecRandNum1;
    Vec4    m_vecRandNum2;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CWindShaderScript);
public:
    CWindShaderScript();
    ~CWindShaderScript();
};

