#pragma once
#include <Engine/CScript.h>
class CMagic_HookScript :
    public CScript
{
private:
    bool    m_bHook;
    Vec3    m_vHookPos;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CMagic_HookScript);

public:
    CMagic_HookScript();
    ~CMagic_HookScript();
};

