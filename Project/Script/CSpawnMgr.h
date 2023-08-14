#pragma once
#include <Engine/CSingleton.h>

class CRoomScript;

struct DoorInfo
{
    int          RoomNum;
    CGameObject* Obj;
};

class CSpawnMgr :
    public CSingleton<CSpawnMgr>
{
    SINGLE(CSpawnMgr);
private:
    int                     m_iCurRoomNum;  // ���� Ȱ����ų ���� ��ȣ
    vector<DoorInfo>        m_vecFence;        // �� ��ȣ�� ���� fence obj
    map<int, CRoomScript*>  m_mapWave;
public:
    void RegisterFence(int _iRoomNum, CGameObject* _pDoor);
    void RegisterWave(int _iRoomNum, CRoomScript* _pWave);
    void SpawnMonster(int _iRoomNum);
    void SetFence(int _iRoomNum, bool _bOpen);
    void DeleteDoor(CGameObject* _pDoor);


};

