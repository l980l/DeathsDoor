#pragma once
#include <Engine\CScript.h>

class CStateScript;

class CBazookaScript :
    public CScript
{
private:
    CStateScript* m_pState;
    CGameObject*  m_pPlayer;

public:
    virtual void begin() override;
    virtual void tick() override;
    void CheckDir();
    void SetState();


public:
    virtual void BeginOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CBazookaScript);

public:
    CBazookaScript();
    CBazookaScript(const CBazookaScript& _Other);
    ~CBazookaScript();
};

