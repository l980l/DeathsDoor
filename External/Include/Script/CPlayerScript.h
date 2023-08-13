#pragma once
#include <Engine\CScript.h>

class CStateScript;
class CPlayerWeaponScript;

class CPlayerScript :
    public CScript
{
private:
    CStateScript*        m_pStateScript;
    CPlayerWeaponScript* m_pSword;
    UINT                 m_iCurMagic;
    bool                 m_bInvincible;
    float                m_fFallCheckTime;
    UINT                 m_imoney;
    UINT                 m_iUpgrade[(UINT)PLAYER_UPGRADE::END];
    bool                 m_bEditorMode;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    void SetInvincible(bool _bInvincible) { m_bInvincible = _bInvincible; }
    void ChangeState(wstring _strStateName);
    UINT GetUseMagic() { return m_iCurMagic; }
    UINT GetMoneyCount() { return m_imoney; }
    UINT AddMoney(UINT _iAddMoney) { m_imoney += _iAddMoney; return m_imoney; }
    void Upgrade(PLAYER_UPGRADE _Type);
    UINT GetUpgrade(PLAYER_UPGRADE _Upgrade) { return m_iUpgrade[(UINT)_Upgrade]; }
    void ChangeMagicState();
    void FallCheck();
    void EditorMode();

private:
    void SetMagicType();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CPlayerScript);

public:
    CPlayerScript();
    ~CPlayerScript();
};

