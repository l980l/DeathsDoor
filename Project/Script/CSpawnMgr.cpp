#include "pch.h"
#include "CSpawnMgr.h"
#include "CRoomScript.h"

CSpawnMgr::CSpawnMgr()
	: m_iCurRoomNum(-1)
	, m_mapWave{}
{
}
CSpawnMgr::~CSpawnMgr()
{
}

void CSpawnMgr::RegisterFence(int _iRoomNum, CFenceScript* _pDoor)
{
	assert(_iRoomNum != -1);
	m_mapWave.find(_iRoomNum)->second->RegisterFence(_pDoor);
}

void CSpawnMgr::RegisterWave(int _iRoomNum, CRoomScript* _pWave)
{
	assert(_iRoomNum != -1);
	m_mapWave.insert(make_pair(_iRoomNum, _pWave));
}

void CSpawnMgr::SpawnMonster(int _iRoomNum)
{
	m_mapWave.find(m_iCurRoomNum)->second->SpawnMst();
}

void CSpawnMgr::ActivateFence(int _iRoomNum, bool _bOpen)
{ 
	m_mapWave[_iRoomNum]->ActivateFence(_bOpen);
}

void CSpawnMgr::ReduceMonsterCount()
{
	m_mapWave.find(m_iCurRoomNum)->second->ReduceMonsterCount();
}

void CSpawnMgr::ReduceGimmickCount()
{
	m_mapWave.find(m_iCurRoomNum)->second->ReduceGimmickCount();
}
