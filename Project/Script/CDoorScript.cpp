#include "pch.h"
#include "CDoorScript.h"
#include "CSpawnMgr.h"

CDoorScript::CDoorScript()
	: CScript((UINT)SCRIPT_TYPE::DOORSCRIPT)
	, m_iRoomNum(-1)
	, m_bOpen(false)
	, m_bClose(false)
	, m_vStartPos{}
	, m_fMoveDistance(0.f)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CDoorScript::CDoorScript(const CDoorScript& _Other)
	:CScript((UINT)SCRIPT_TYPE::DOORSCRIPT)
	, m_iRoomNum(-1)
	, m_bOpen(false)
	, m_bClose(false)
	, m_fMoveDistance(0.f)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CDoorScript::~CDoorScript()
{
}

void CDoorScript::begin()
{
	CSpawnMgr::GetInst()->RegisterDoor(m_iRoomNum, GetOwner());
}

void CDoorScript::tick()
{
	if (m_bOpen || m_bClose)
	{
		m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
		if (m_fMoveDistance > 500.f)
		{
			m_bClose = false;
			m_bOpen = false;
		}
	}
}

void CDoorScript::CloseDoor()
{
	m_bClose = true;
	m_vStartPos = Transform()->GetWorldPos();
}

void CDoorScript::OpenDoor()
{
	m_bOpen = true;
	m_vStartPos = Transform()->GetWorldPos();
}

void CDoorScript::SaveToLevelFile(FILE* _File)
{
}

void CDoorScript::LoadFromLevelFile(FILE* _File)
{
}
