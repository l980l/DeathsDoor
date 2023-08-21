#include "pch.h"
#include "CFenceScript.h"
#include <Engine/CPhysXMgr.h>

CFenceScript::CFenceScript()
	: CScript((UINT)SCRIPT_TYPE::WALLSCRIPT)
	, m_iRoomNum(-1)
	, m_vStartPos{}
	, m_fMoveDistance(0.f)
	, m_bActive(false)
	, m_bOpen(false)
{
}

CFenceScript::~CFenceScript()
{
}

void CFenceScript::tick()
{
	// 활성화되지 않았다면 return
	if (!m_bActive)
		return;

	// Open이라면 아래로 Close라면 위로 방향을 줌
	Vec3 vCurPos = Transform()->GetWorldPos();
	float fFenceDir = 0.f;

	if (m_bOpen)
		fFenceDir = 50.f * DT;
	else
		fFenceDir = -50.f * DT;

	Transform()->SetRelativePos(vCurPos.x, vCurPos.y + fFenceDir, vCurPos.z);

	// 일정 거리 이상 이동했다면 false
	m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
	if (m_fMoveDistance > 100.f)
	{
		CPhysXMgr::GetInst()->CreateStaticCube(vCurPos, Vec3(100.f), GetOwner());
		m_bActive = false;
	}
}

void CFenceScript::ActivateFence(bool _bOpen)
{
	m_bActive = true;
	m_bOpen = _bOpen;
	m_vStartPos = Transform()->GetWorldPos();
	if (_bOpen)
		CPhysXMgr::GetInst()->CreateStaticCube(m_vStartPos, Vec3(500.f), GetOwner());
	else
		CPhysXMgr::GetInst()->ReleaseStatic(Rigidbody()->GetRigidStatic());
}

void CFenceScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iRoomNum, sizeof(int), 1, _File);
}

void CFenceScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iRoomNum, sizeof(int), 1, _File);
}
