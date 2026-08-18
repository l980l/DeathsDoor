#include "pch.h"
#include "CSpawnMgr.h"
#include "CRoomScript.h"
#include "CFenceScript.h"

CSpawnMgr::CSpawnMgr()
    : m_iCurRoomNum(-1)
    , m_mapRoom{}
{
}

CSpawnMgr::~CSpawnMgr()
{
}

void CSpawnMgr::RegisterFence(int _iRoomNum, CFenceScript* _pFence)
{
	if (m_iCurRoomNum < 0)
		return;

    FenceInfo tFenceInfo;
    tFenceInfo.RoomNum = _iRoomNum;
    tFenceInfo.Fence   = _pFence;
    m_vecFence.push_back(tFenceInfo);
}

void CSpawnMgr::RegisterRoom(int _iRoomNum, CRoomScript* _pRoom)
{
	if (m_iCurRoomNum < 0)
		return;

    m_mapRoom.insert(make_pair(_iRoomNum, _pRoom));
}

void CSpawnMgr::SpawnMonster(int _iRoomNum) const
{
	if (m_iCurRoomNum < 0)
		return;

    m_mapRoom.find(m_iCurRoomNum)->second->SpawnMst();
}

void CSpawnMgr::ActivateFence(int _iRoomNum, bool _bOpen)
{
	if (m_iCurRoomNum < 0)
		return;

    m_iCurRoomNum = _iRoomNum;
    if (!_bOpen)
        SpawnMonster(_iRoomNum);
    for (auto& iter : m_vecFence)
    {
        if (_iRoomNum == iter.RoomNum)
            iter.Fence->ActivateFence(_bOpen);
    }
}

void CSpawnMgr::ReduceMonsterCount() const
{
    if (m_iCurRoomNum < 0)
        return;

    if (CRoomScript* room = m_mapRoom.find(m_iCurRoomNum)->second)
        room->ReduceMonsterCount();
}

void CSpawnMgr::ReduceGimmickCount() const
{
	if (m_iCurRoomNum < 0)
		return;

	if (CRoomScript* room = m_mapRoom.find(m_iCurRoomNum)->second)
		room->ReduceGimmickCount();
}

void CSpawnMgr::Clear()
{
    m_iCurRoomNum = -1;
    m_mapRoom.clear();
    m_vecFence.clear();
}
