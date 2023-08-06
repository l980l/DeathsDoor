#include "pch.h"
#include "CFenseScript.h"

CFenseScript::CFenseScript() :
	CScript(SCRIPT_TYPE::FENSESCRIPT)
{
}

CFenseScript::~CFenseScript()
{
}

void CFenseScript::begin()
{
}

void CFenseScript::tick()
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

void CFenseScript::CloseDoor()
{
	m_bClose = true;
	m_vStartPos = Transform()->GetWorldPos();
}

void CFenseScript::OpenDoor()
{
	m_bOpen = true;
	m_vStartPos = Transform()->GetWorldPos();
}
