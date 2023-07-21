#pragma once
#include <Engine\CScript.h>

class CStateScript;

class CMonsterScript :
    public CScript
{
private:
    CStateScript*   m_pStateScript;
    CGameObject*    m_pPlayer;
    bool            m_bDetect;

public:
    CGameObject*    GetPlayer() { return m_pPlayer; }
    void            SetDetect(bool _bDetect) { m_bDetect = _bDetect; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;

    CLONE(CMonsterScript);
public:
    CMonsterScript(UINT SCRIPT_TYPE);
    ~CMonsterScript();
  
    friend class CBazookaScript;
};


