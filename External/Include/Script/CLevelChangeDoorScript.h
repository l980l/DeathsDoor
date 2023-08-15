#pragma once
#include <Engine/CScript.h>

class CLevelChangeDoorScript :
    public CScript
{
private:
    LEVEL_TYPE m_tChangeLevel;
public:
    virtual void begin() override;
    virtual void tick() override {};
    void SetLevelType(LEVEL_TYPE _tLevelType) { m_tChangeLevel = _tLevelType; }

    virtual void OnOverlap(CCollider3D* _Other) override;
private:
    CLONE(CLevelChangeDoorScript);
public:
    CLevelChangeDoorScript();
    ~CLevelChangeDoorScript();
};

