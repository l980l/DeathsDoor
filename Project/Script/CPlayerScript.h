#pragma once
#include <Engine/CScript.h>

class CStateScript;
class CPlayerWeaponScript;

class CPlayerScript :
    public CScript
{
    CStateScript*        m_pStateScript;
    CPlayerWeaponScript* m_pSword;
    UINT                 m_iCurMagic;
    UINT                 m_imoney;
    UINT                 m_arrUpgrade[static_cast<UINT>(PLAYER_UPGRADE::END)];
    float                m_fFallCheckTime;
    bool                 m_bInvincible;
    bool                 m_bEditorMode;
    bool                 m_bDisableMove;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    void SetInvincible(bool _bInvincible) { m_bInvincible = _bInvincible; }
    void ChangeState(wstring _strStateName) const;
    UINT GetUseMagic() const { return m_iCurMagic; }
    UINT GetMoneyCount() const { return m_imoney; }

    UINT AddMoney(UINT _iAddMoney)
    {
        m_imoney += _iAddMoney;
        return m_imoney;
    }

    void Upgrade(PLAYER_UPGRADE _Type);
    UINT GetUpgrade(PLAYER_UPGRADE _Upgrade) const { return m_arrUpgrade[static_cast<UINT>(_Upgrade)]; }
    void ChangeMagicState();
    void FallCheck();
    void EditorMode();
    void SetMoveAble(bool _bAble) { m_bDisableMove = !_bAble; }

    bool IsAbleMove() const
    {
        bool bAble = !m_bDisableMove;
        return bAble;
    }

private:
    void SetMagicType();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CPlayerScript);

    CPlayerScript();
    virtual ~CPlayerScript() override;
};
