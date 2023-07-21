#pragma once
#include <Engine\CScript.h>

class CStateScript;
class dtNavMesh;

class CPlayerScript :
    public CScript
{
private:
    CStateScript* m_pStateScript;
    float           m_bInvincible;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    void SetInvincible(bool _bInvincible) { m_bInvincible = _bInvincible; }

private:
    void Shoot();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CPlayerScript);

public:
    CPlayerScript();
    ~CPlayerScript();
};

