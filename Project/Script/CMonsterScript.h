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
    bool            m_bPaperBurnEffect;     // PaperBurn 효과를 줄지.
    bool            m_bSendDeadTime;        // 사망시간을 이미 보냈는지. 

public:
    CGameObject*    GetPlayer() { return m_pPlayer; }
    bool            GetDetect() { return m_bDetect; }
    void            SetDetect(bool _bDetect) { m_bDetect = _bDetect; }
    bool            GetPaperBurnEffect() const { return m_bPaperBurnEffect;}
    void            SetPaperBurnEffect(bool value) { m_bPaperBurnEffect = value;}

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CMonsterScript);
public:
    CMonsterScript(UINT SCRIPT_TYPE);
    ~CMonsterScript();
  
    friend class CBazookaScript;
    friend class CLurkerScript;
    friend class CGruntScript;
    friend class CCrowBossScript;
    friend class CBatScript;
    friend class CGrimKnightScript;
    friend class CKnightScript;
    friend class CGhostScript;
};


