#pragma once
#include <Engine/CScript.h>

class CStateScript;

class CPlayerWeaponScript :
    public CScript
{
private:
    CStateScript*   m_pStateScript;
    UINT            m_tCurMagic;
    float           m_bInvincible;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;
    void SetInvincible(bool _bInvincible) { m_bInvincible = _bInvincible; }

    UINT GetUseMagic() { return m_tCurMagic; }

private:

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CPlayerWeaponScript);

public:
    CPlayerWeaponScript();
    ~CPlayerWeaponScript();
};

