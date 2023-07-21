#pragma once
#include <Engine/CScript.h>
#include "CMonsterScript.h"

class CKnightScript :
    public CMonsterScript
{
private:
    Stat m_stat;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CKnightScript);

public:
    CKnightScript();
    CKnightScript(const CKnightScript& _Other);
    ~CKnightScript();
};

