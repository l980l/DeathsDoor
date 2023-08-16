#pragma once
#include "CMonsterScript.h"
class CCrowBossScript :
    public CMonsterScript
{
private:
    Vec3            m_PlayerPos;
    Vec3            m_MonsterToPlayerDir;
    float           m_fPlayerDistance;
    bool            m_bStarePlayer;
    float           m_fPrevHP;          // ���� HP. HP�� �پ��� ��, ������ ���带 ����ϱ� ���� ���.
    CGameObject*    m_pCrowBossFeather;

public:
    Vec3 GetPlayerPos() { return m_PlayerPos; }
    Vec3 GetMonsterToPlayerDir() { return m_MonsterToPlayerDir; }
    float GetPlayerDistance() { return m_fPlayerDistance; }

    bool GetStarePlayer() { return m_bStarePlayer; }
    void SetStarePlayer(bool _bStarePlayer) { m_bStarePlayer = _bStarePlayer; }
    void DestoryFeather() { if (m_pCrowBossFeather) m_pCrowBossFeather->SetLifeSpan(0.f); }

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCrowBossScript);

public:
    CCrowBossScript();
    CCrowBossScript(const CCrowBossScript& _Other);
    ~CCrowBossScript();
};

