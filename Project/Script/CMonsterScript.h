#pragma once
#include <Engine\CScript.h>

class CStateScript;

class CMonsterScript :
    public CScript
{
private:
    CStateScript*   m_pStateScript;
    CGameObject* m_pPlayer;
    bool                    m_bDetect;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


