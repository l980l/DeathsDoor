#pragma once
#include "CMonsterScript.h"

class CGruntScript :
    public CMonsterScript
{
private:
    Vec3    m_vPlayerPos;
    Vec3    m_vMonsterToPlayerDir;
    float   m_fPlayerDistance;
    float   m_fAttackRange;     // ���� ����. 
    int     m_iNailAttackCount;  // ���� ���� Ƚ��. 2ȸ�� ���� ����.
    bool    m_bStarePlayer;
    float   m_fPrevHP;          // ���� HP. HP�� �پ��� ��, ������ ���带 ����ϱ� ���� ���.

public:
    Vec3 GetPlayerPos() { return m_vPlayerPos; }
    Vec3 GetMonsterToPlayerDir() { return m_vMonsterToPlayerDir; }
    float GetPlayerDistance() { return m_fPlayerDistance; }

    float GetAttackRange() { return m_fAttackRange; }

    int GetNailAttackCount() { return m_iNailAttackCount; }
    void CountNailAttack();

    bool GetStarePlayer() { return m_bStarePlayer; }
    void SetStarePlayer(bool _bStarePlayer) { m_bStarePlayer = _bStarePlayer; }

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

