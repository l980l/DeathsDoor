#include "pch.h"
#include "CWallScript.h"

CWallScript::CWallScript()
	: CScript((UINT)SCRIPT_TYPE::WALLSCRIPT)
{
}

CWallScript::~CWallScript()
{
}

void CWallScript::tick()
{
	if (m_bOpen || m_bClose)
	{
		Vec3 vCurPos = Transform()->GetWorldPos();
		if (m_bOpen)
		{
			Transform()->SetRelativePos(vCurPos.x, vCurPos.y + 50.f * DT, vCurPos.z);
		}
		else
		{
			Transform()->SetRelativePos(vCurPos.x, vCurPos.y - 50.f * DT, vCurPos.z);
		}
		m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
		if (m_fMoveDistance > 100.f)
		{
			m_bClose = false;
			m_bOpen = false;
		}
	}
}

void CWallScript::CloseDoor()
{
	m_bClose = true;
	m_vStartPos = Transform()->GetWorldPos();
}

void CWallScript::OpenDoor()
{
	m_bOpen = true;
	m_vStartPos = Transform()->GetWorldPos();
}

void CWallScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iRoomNum, sizeof(int), 1, _File);
}

void CWallScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iRoomNum, sizeof(int), 1, _File);
}
