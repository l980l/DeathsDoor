#pragma once
#include "CMonsterScript.h"

class CBazookaScript :
    public CMonsterScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CBazookaScript);

public:
    CBazookaScript();
    CBazookaScript(const CBazookaScript& _Other);
    ~CBazookaScript();
};

