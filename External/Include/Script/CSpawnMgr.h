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
    vector<DoorInfo>        m_vecDoor;        // �� ��ȣ�� ���� �� obj
    map<int, CRoomScript*>  m_mapWave;
    int                     m_iGimmickCount;  // ���� ���� ���ؼ� Ȱ��ȭ�ؾ� �� ���

public:
    void RegisterDoor(int _iRoomNum, CGameObject* _pDoor);
    void RegisterWave(int _iRoomNum, CRoomScript* _pWave);
    void SpawnMonster(int _iRoomNum);
    void ModifyDoor(int _iRoomNum, bool _bOpen);
    void ReduceMonsterCount();
    void ReduceGimmickCount();
    void DeleteDoor(CGameObject* _pDoor);


};

