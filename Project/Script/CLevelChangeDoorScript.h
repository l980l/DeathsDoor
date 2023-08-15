#pragma once
#include <Engine/CScript.h>

class CLevelChangeDoorScript :
    public CScript
{
private:
    int m_iChangeLevel;
public:
    virtual void begin() override;
    virtual void tick() override {};
    void SetLevelType(int _tLevelType) { m_iChangeLevel = (int)_tLevelType; }

    virtual void OnOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
private:
    CLONE(CLevelChangeDoorScript);
public:
    CLevelChangeDoorScript();
    ~CLevelChangeDoorScript();
};

