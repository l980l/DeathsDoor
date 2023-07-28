#include "pch.h"
#include "CSpawnMgr.h"
#include "CRoomScript.h"
#include "CDoorScript.h"

CSpawnMgr::CSpawnMgr()
	: m_iCurRoomNum(-1)
	, m_vecDoor{}
	, m_mapWave{}
	, m_iGimmickCount(0)
{

}
CSpawnMgr::~CSpawnMgr()
{

}

void CSpawnMgr::RegisterDoor(int _iRoomNum, CGameObject* _pDoor)
{
	assert(_iRoomNum != -1);
	DoorInfo Info;
	Info.RoomNum = _iRoomNum;
	Info.Obj = _pDoor;
	m_vecDoor.push_back(Info);
}

void CSpawnMgr::RegisterWave(int _iRoomNum, CRoomScript* _pWave)
{
	assert(_iRoomNum != -1);
	if (_iRoomNum == 1)
		m_mapWave.clear();
	m_mapWave.insert(make_pair(_iRoomNum, _pWave));
}

void CSpawnMgr::SpawnMonster(int _iRoomNum)
{
	m_iCurRoomNum = _iRoomNum;
	m_mapWave.find(m_iCurRoomNum)->second->SpawnMst();
}

void CSpawnMgr::ModifyDoor(int _iRoomNum, bool _bOpen)
{
	if(_bOpen)
	{
		for (size_t i = 0; i < m_vecDoor.size(); ++i)
		{
			if (_iRoomNum == m_vecDoor[i].RoomNum)
				m_vecDoor[i].Obj->GetScript<CDoorScript>()->OpenDoor();
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecDoor.size(); ++i)
		{
			if (_iRoomNum == m_vecDoor[i].RoomNum)
				m_vecDoor[i].Obj->GetScript<CDoorScript>()->CloseDoor();
		}
	}
}

void CSpawnMgr::ReduceMonsterCount()
{
	CRoomScript* Wave = m_mapWave.find(m_iCurRoomNum)->second;
	Wave->MinusMstCount();
}

void CSpawnMgr::ReduceGimmickCount()
{
	CRoomScript* Wave = m_mapWave.find(m_iCurRoomNum)->second;
	Wave->MinusMstCount();
}

void CSpawnMgr::DeleteDoor(CGameObject* _pDoor)
{
	vector<DoorInfo>::iterator iter = m_vecDoor.begin();
	for (; iter != m_vecDoor.end(); ++iter)
	{
		if (iter->Obj == _pDoor)
		{
			m_vecDoor.erase(iter);
			return;
		}
	}
}
