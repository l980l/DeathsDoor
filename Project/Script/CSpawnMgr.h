#pragma once
#include <Engine/CSingleton.h>

class CRoomScript;
class CFenceScript;

class CSpawnMgr :
    public CSingleton<CSpawnMgr>
{
    SINGLE(CSpawnMgr);
private:
    int                     m_iCurRoomNum;     // ���� Ȱ��ȭ �� ���� ��ȣ
    map<int, CRoomScript*>  m_mapRoom;
    map<int, CFenceScript*> m_mapFence;         // �� ��ȣ�� ���� fence obj

public:
    void RegisterFence(int _iRoomNum, CFenceScript* _pDoor);
    void RegisterRoom(int _iRoomNum, CRoomScript* _pWave);
    void SpawnMonster(int _iRoomNum);
    void ActivateFence(int _iRoomNum, bool _bOpen);

    void ReduceMonsterCount();
    void ReduceGimmickCount();
};

