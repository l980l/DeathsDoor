#include "pch.h"
#include "CCrowBossStomp.h"
#include "CCrowBossScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CGameCameraScript.h"
#include <Engine/CRenderMgr.h>

void CCrowBossStomp::Enter()
{
	GetOwner()->Animator3D()->Play(10, false);

	if(m_Dir.Length())
		m_Dir = GetOwner()->GetScript<CCrowBossScript>()->GetMonsterToPlayerDir();

	if(!m_fDistance)
		m_fDistance = GetOwner()->GetScript<CCrowBossScript>()->GetPlayerDistance();

	m_fTime = 0.f;
	m_bCameraShake = false;
}

void CCrowBossStomp::tick()
{
	// Camera Shake
	m_fTime += DT;
	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();

	if (!m_bCameraShake && fRatio >= 0.8f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);
		m_bCameraShake = true;
	}

	// ���� �浹ü ������
	CGameObject* MonsterAtack = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\MonsterAttack.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 0.2f);

	MonsterAtack->Collider3D()->SetOffsetPos(GetOwner()->Collider3D()->GetOffsetPos());
	MonsterAtack->Collider3D()->SetOffsetScale(GetOwner()->Collider3D()->GetOffsetScale());

	// �ִϸ��̼� ����ð����� �÷��̾��� ��ġ���� �����ϱ� ���� Velocity.
	Vec3 Velocity = m_Dir * (m_fDistance / (float)GetOwner()->Animator3D()->GetCurClipTimeLength());
	Velocity *= DT;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	// �ִϸ��̼��� ���� ���.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"RightSpin");
	}
}

void CCrowBossStomp::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}

CCrowBossStomp::CCrowBossStomp() :
	m_fDistance(0.f)
	, m_fTime(0.f)
	, m_bCameraShake(false)
{
}

CCrowBossStomp::~CCrowBossStomp()
{
}
