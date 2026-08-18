#pragma once
#include <Engine/CScript.h>

class CLevelChangeDoorScript :
    public CScript
{
    int m_iChangeLevel;

public:
    virtual void tick() override
    {
    };

    void SetLevelType(int _tLevelType) { m_iChangeLevel = _tLevelType; }

    virtual void OnOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CLevelChangeDoorScript);

    CLevelChangeDoorScript();
    virtual ~CLevelChangeDoorScript() override;
};
