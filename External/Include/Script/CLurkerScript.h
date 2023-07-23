#pragma once
#include "CMonsterScript.h"

class CLurkerScript :
    public CMonsterScript
{
private:
    Vec3    m_PlayerPos;
    Vec3    m_MonsterToPlayerDir;
    float   m_fPlayerDistance;

    float   m_fAttackRange;     // 공격 범위. 

public:
    Vec3 GetPlayerPos() { return m_PlayerPos; }
    Vec3 GetMonsterToPlayerDir() { return m_MonsterToPlayerDir; }
    float GetPlayerDistance() { return m_fPlayerDistance; }

    float GetAttackRange() { return m_fAttackRange; }

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