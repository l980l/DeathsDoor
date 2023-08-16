#pragma once
#include <Engine/CScript.h>
class CRoomScript :
    public CScript
{
private:
    int                 m_iRoomNum;     // ���� ���̺긦 �߻���ų ���� �� ��ȣ
    int                 m_iRemainMst;   // ���� ���� ��
    int                 m_iRemainGimmik;  // ���� ���� ���ؼ� Ȱ��ȭ�ؾ� �� ���
    int                 m_iCurWaveNum;  // ���� Wave
    int                 m_iMaxWaveNum;  // �ִ� Wave
    int                 m_prevMonsterNum;
    vector<SpawnInfo>   m_vecWave[2];   // ���� ������ ���� Wave vector
    bool                m_bActive;      // Ȱ�� ����
    bool                m_bSpawn;
    bool                m_bLastWave;
    bool                m_bWaveStart;
    bool                m_bStoneHit;
public:
    virtual void begin() override;
    virtual void tick() override;

private:
    void SpawnMst();

public:
    void SetWaveCount(int _iWaveCount) { m_iMaxWaveNum = _iWaveCount; }
    void SetRoomNum(int _iRoomNum) { m_iRoomNum = _iRoomNum; }
    void SetWaveInfo(int _iWaveNum, vector<SpawnInfo> _mapInfo);
    void ReduceMonsterCount();
    void ReduceGimmickCount();
    vector<SpawnInfo> GetWaveInfo(int _iWaveNum) { return m_vecWave[_iWaveNum]; }
    void AddWaveMst(int _iWavwNum, wstring _wstrPrefName, Vec3 _vSpawnPos);
    virtual void BeginOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CRoomScript);
public:
    CRoomScript();
    CRoomScript(const CRoomScript& _Other);
    ~CRoomScript();

    friend class CSpawnMgr;
};

