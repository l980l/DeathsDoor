#include "pch.h"
#include "CFenseScript.h"
#include "CSpawnMgr.h"
#include <Engine/CPhysXMgr.h>

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
	if (GetOwner() == nullptr)
		return;

	if (m_bOpen || m_bClose)
	{
		Vec3 vCurPos = Transform()->GetWorldPos();
		if (m_bOpen)
		{
			Transform()->SetRelativePos(vCurPos.x, vCurPos.y + 100.f * DT, vCurPos.z);
		}
		else if(m_bClose)
		{
			CPhysXMgr::GetInst()->ReleaseStatic(rStatic);
			Transform()->SetRelativePos(vCurPos.x, vCurPos.y - 100.f * DT, vCurPos.z);
		}
		m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
		if (m_fMoveDistance > 200.f && m_bOpen)
		{
			GetOwner()->AddComponent(new CRigidbody);
			rStatic = CPhysXMgr::GetInst()->CreateStaticCube(Vec3(GetOwner()->Transform()->GetWorldPos()), Vec3(50.f, 50.f, 50.f), GetOwner());
			m_bOpen = false;
		}
		if (m_fMoveDistance > 200.f && m_bClose)
		{
			m_bClose = false;
			GetOwner()->SetLifeSpan(0.5f);
		}
	}
}

void CFenseScript::CloseFence()
{
	m_bClose = true;
	m_vStartPos = Transform()->GetWorldPos();
}

void CFenseScript::OpenFence()
{
	m_bOpen = true;
	m_vStartPos = Transform()->GetWorldPos();
}
