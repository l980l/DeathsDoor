#include "pch.h"
#include "CSpawnMgr.h"
#include "CRoomScript.h"

CSpawnMgr::CSpawnMgr()
	: m_iCurRoomNum(-1)
	, m_mapRoom{}
{
}
CSpawnMgr::~CSpawnMgr()
{
}

void CSpawnMgr::RegisterFence(int _iRoomNum, CFenceScript* _pDoor)
{
	assert(_iRoomNum != -1);
	m_map.find(_iRoomNum)->second->RegisterFence(_pDoor);
}

void CSpawnMgr::RegisterRoom(int _iRoomNum, CRoomScript* _pWave)
{
	assert(_iRoomNum != -1);
	m_mapRoom.insert(make_pair(_iRoomNum, _pWave));
}

void CSpawnMgr::SpawnMonster(int _iRoomNum)
{
	assert(_iRoomNum != -1);
	m_mapRoom.find(m_iCurRoomNum)->second->SpawnMst();
}

void CSpawnMgr::ActivateFence(int _iRoomNum, bool _bOpen)
{
	assert(_iRoomNum != -1);
	m_iCurRoomNum = _iRoomNum;
	m_mapRoom[_iRoomNum]->ActivateFence(_bOpen);
}

void CSpawnMgr::ReduceMonsterCount()
{
	assert(m_iCurRoomNum != -1);
	m_mapRoom.find(m_iCurRoomNum)->second->ReduceMonsterCount();
}

void CSpawnMgr::ReduceGimmickCount()
{
	assert(m_iCurRoomNum != -1);
	m_mapRoom.find(m_iCurRoomNum)->second->ReduceGimmickCount();
}
