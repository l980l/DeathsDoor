#pragma once
#include "CMonsterScript.h"
class CGhostScript :
    public CMonsterScript
{
private:
    Stat m_stat;
    bool recognizeCheck;
    bool onCollision;
public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CGhostScript);

public:
    CGhostScript();
    CGhostScript(const CGhostScript& _Other);
    ~CGhostScript();
};

