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
	if (m_bOpen || m_bClose)
	{
		Vec3 vCurPos = Transform()->GetWorldPos();
		if (m_bOpen)
		{
			Transform()->SetRelativePos(vCurPos.x, vCurPos.y + 100.f * DT, vCurPos.z);
		}
		else if(m_bClose)
		{
			GetOwner()->SetLifeSpan(0.f);
			/*CPhysXMgr::GetInst()->ReleaseStatic(rStatic);
			Transform()->SetRelativePos(vCurPos.x, vCurPos.y - 100.f * DT, vCurPos.z);*/
		}
		m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
		if (m_fMoveDistance > 200.f && m_bOpen)
		{
			GetOwner()->AddComponent(new CRigidbody);
			rStatic = CPhysXMgr::GetInst()->CreateStaticCube(Vec3(GetOwner()->Transform()->GetWorldPos()), Vec3(100.f, 100.f, 100.f), GetOwner());
			m_bOpen = false;
		}
		if (m_fMoveDistance > 200.f && m_bClose)
		{
			m_bClose = false;
			
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
