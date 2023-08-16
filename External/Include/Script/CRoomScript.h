#pragma once
#include <Engine/CScript.h>
class CRoomScript :
    public CScript
{
private:
    int                 m_iRoomNum;     // 몬스터 웨이브를 발생시킬 현재 방 번호
    int                 m_iRemainMst;   // 남은 몬스터 수
    int                 m_iRemainGimmik;  // 문을 열기 위해서 활성화해야 할 기믹
    int                 m_iCurWaveNum;  // 현재 Wave
    int                 m_iMaxWaveNum;  // 최대 Wave
    int                 m_prevMonsterNum;
    vector<SpawnInfo>   m_vecWave[2];   // 스폰 정보를 담은 Wave vector
    bool                m_bActive;      // 활성 여부
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

