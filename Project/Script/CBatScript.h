#pragma once
#include <Engine\CScript.h>
#include "CMonsterScript.h"

class CBatScript    :
    public CMonsterScript
{
private:
    Stat m_stat;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CBatScript);

public:
    CBatScript();
    CBatScript(const CBatScript& _Other);
    ~CBatScript();

};
