#pragma once
#include <Engine\CScript.h>

class CStateScript;

class CMonsterScript :
    public CScript
{
private:
    CStateScript*   m_pState;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


