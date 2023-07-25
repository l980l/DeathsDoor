#pragma once
#include "CMonsterScript.h"

class CGruntScript :
    public CMonsterScript
{
private:
    Vec3    m_PlayerPos;
    Vec3    m_MonsterToPlayerDir;
    float   m_fPlayerDistance;

    float   m_fAttackRange;     // ���� ����. 

    int     m_iNailAttackCount;  // ���� ���� Ƚ��. 2ȸ�� ���� ����.

public:
    Vec3 GetPlayerPos() { return m_PlayerPos; }
    Vec3 GetMonsterToPlayerDir() { return m_MonsterToPlayerDir; }
    float GetPlayerDistance() { return m_fPlayerDistance; }

    float GetAttackRange() { return m_fAttackRange; }

    int GetNailAttackCount() { return m_iNailAttackCount; }
    void CountNailAttack();

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CGruntScript);

public:
    CGruntScript();
    CGruntScript(const CGruntScript& _Other);
    ~CGruntScript();
};

