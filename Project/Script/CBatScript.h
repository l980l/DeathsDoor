#pragma once
#include <Engine/CScript.h>
#include "CMonsterScript.h"

class CBatScript :
    public CMonsterScript
{
    bool m_bRecognizeCheck;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;
    bool         GetRecognizeCheck() const { return m_bRecognizeCheck; }
    CLONE(CBatScript);

    CBatScript();
    virtual ~CBatScript() override;
};
