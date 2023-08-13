#include "pch.h"
#include "CSpawnMgr.h"
#include "CRoomScript.h"
#include "CFenseScript.h"

CSpawnMgr::CSpawnMgr()
	: m_iCurRoomNum(-1)
	, m_vecFence{}
	, m_mapWave{}
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
	m_vecFence.push_back(Info);
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

void CSpawnMgr::SetFence(int _iRoomNum, bool _bOpen)
{
	if(_bOpen)
	{
		for (size_t i = 0; i < m_vecFence.size(); ++i)
		{
			if (_iRoomNum == m_vecFence[i].RoomNum)//fence의 방 번호가 room nb라면
				m_vecFence[i].Obj->GetScript<CFenseScript>()->OpenFence(); //해당 fence 오픈 위로 올라감
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecFence.size(); ++i)
		{
			if (_iRoomNum == m_vecFence[i].RoomNum)
				m_vecFence[i].Obj->GetScript<CFenseScript>()->CloseFence();
		}
	}
}

void CSpawnMgr::DeleteDoor(CGameObject* _pDoor)
{
	vector<DoorInfo>::iterator iter = m_vecFence.begin();
	for (; iter != m_vecFence.end(); ++iter)
	{
		if (iter->Obj == _pDoor)
		{
			m_vecFence.erase(iter);
			return;
		}
	}
}
