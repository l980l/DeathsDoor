#pragma once
#include<Engine/CScript.h>
#include "CMonsterScript.h"
class CGrimKnightScript :
    public CMonsterScript
{
private:
    Stat m_stat;
    bool recognizeCheck;
    bool retrace;
    bool onCollision;
    int m_hitCount;

public:
    void SetOnCollision(bool onCol) { onCollision = onCol; }
    int GetHitCount() { return m_hitCount; }
public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CGrimKnightScript);

public:
    CGrimKnightScript();
    CGrimKnightScript(const CGrimKnightScript& _Other);
    ~CGrimKnightScript();
};

