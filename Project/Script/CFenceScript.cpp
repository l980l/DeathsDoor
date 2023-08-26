#include "pch.h"
#include "CFenceScript.h"
#include <Engine/CPhysXMgr.h>
#include "CSpawnMgr.h"

CFenceScript::CFenceScript()
	: CScript((UINT)SCRIPT_TYPE::FENCESCRIPT)
	, m_iRoomNum(-1)
	, m_pStatic(nullptr)
	, m_vStartPos{}
	, m_fMoveDistance(0.f)
	, m_bActive(false)
	, m_bOpen(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNumber");
}

CFenceScript::~CFenceScript()
{
}

void CFenceScript::begin()
{
	CSpawnMgr::GetInst()->RegisterFence(m_iRoomNum, this);
}

void CFenceScript::tick()
{
	// Ȱ��ȭ���� �ʾҴٸ� return
	if (!m_bActive)
		return;

	// Open�̶�� �Ʒ��� Close��� ���� ������ ��
	Vec3 vCurPos = Transform()->GetWorldPos();
	float fFenceDir = 0.f;
	if (m_bOpen)
		fFenceDir = -150.f * DT;
	else
		fFenceDir = 150.f * DT;
	vCurPos.y += fFenceDir;

	Transform()->SetRelativePos(vCurPos);

	// ���� �Ÿ� �̻� �̵��ߴٸ� false
	m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
	if (m_fMoveDistance > 800.f * Transform()->GetRelativeScale().x)
	{
		m_bActive = false;
		m_fMoveDistance = 0.f;
	}
}

void CFenceScript::ActivateFence(bool _bOpen)
{
	m_bActive = true;
	m_bOpen = _bOpen;
	m_vStartPos = Transform()->GetWorldPos();
	if(!Rigidbody())
		GetOwner()->AddComponent(new CRigidbody);
	if (_bOpen)
		CPhysXMgr::GetInst()->ReleaseStatic(m_pStatic);
	else
		CPhysXMgr::GetInst()->CreateStaticCube(m_vStartPos, Vec3(500.f * Transform()->GetRelativeScale().x), GetOwner());
}

void CFenceScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iRoomNum, sizeof(int), 1, _File);
}

void CFenceScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iRoomNum, sizeof(int), 1, _File);
}
