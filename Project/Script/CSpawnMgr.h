#pragma once
#include <Engine/CSingleton.h>

class CRoomScript;
class CFenceScript;

class CSpawnMgr :
    public CSingleton<CSpawnMgr>
{
    SINGLE(CSpawnMgr);
private:
    int                     m_iCurRoomNum;     // 현재 활성화 된 방의 번호
    map<int, CRoomScript*>  m_mapWave;

public:
    void RegisterFence(int _iRoomNum, CFenceScript* _pDoor);
    void RegisterWave(int _iRoomNum, CRoomScript* _pWave);
    void SpawnMonster(int _iRoomNum);
    void ActivateFence(int _iRoomNum, bool _bOpen);

    void ReduceMonsterCount();
    void ReduceGimmickCount();
};

