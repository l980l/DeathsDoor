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
    int                     m_iCurRoomNum;  // 현재 활성시킬 방의 번호
    vector<DoorInfo>        m_vecDoor;        // 각 번호를 가진 문 obj
    map<int, CRoomScript*>  m_mapWave;

public:
    void RegisterDoor(int _iRoomNum, CGameObject* _pDoor);
    void RegisterWave(int _iRoomNum, CRoomScript* _pWave);
    void SpawnMonster(int _iRoomNum);
    void ModifyDoor(int _iRoomNum, bool _bOpen);
    void DeleteDoor(CGameObject* _pDoor);


};

