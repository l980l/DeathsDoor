#pragma once
#include "CMonsterScript.h"

class CLurkerScript :
    public CMonsterScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CLurkerScript);

public:
    CLurkerScript();
    CLurkerScript(const CLurkerScript& _Other);
    ~CLurkerScript();
};