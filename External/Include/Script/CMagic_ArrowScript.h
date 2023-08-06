#pragma once
#include <Engine/CScript.h>
class CMagic_ArrowScript :
    public CScript
{
private:
    Vec3    m_vDir;
    float   m_fSpeed;
    float   m_fDamage;

public:
    void SetDir(Vec3 _vDir) { m_vDir = _vDir.Normalize(); }
    void SetDamege(float _fDamege) { m_fDamage = _fDamege; }
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CMagic_ArrowScript);

public:
    CMagic_ArrowScript();
    ~CMagic_ArrowScript();
};

