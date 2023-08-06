#pragma once
#include <Engine\CScript.h>

class CStateScript;

class CNaviTestScript :
    public CScript
{
private:
    CStateScript* m_pStateScript;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CNaviTestScript);

    CNaviTestScript();
    ~CNaviTestScript();
};

