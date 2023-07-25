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
    CGameObject*         m_pDustEffect;
    UINT                 m_iCurMagic;
    bool                 m_bInvincible;
    Vec3                 m_vDir;
    float                m_fDir;
    float                m_fDiff;

public:
    void SetDir(float _fDir) { m_fDir = _fDir; }
    void SetDiff(float _fDiff) { m_fDiff = _fDiff; }
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;
    void SetInvincible(bool _bInvincible) { m_bInvincible = _bInvincible; }
    void ChangeState(wstring _strStateName);
    UINT GetUseMagic() { return m_iCurMagic; }
    void ChangeMagicState();
    Vec3 GetDir() { return m_vDir; }

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

