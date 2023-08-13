#include "pch.h"
#include "CPlyMagic_Arrow.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"
#include "CMagic_ArrowScript.h"
#include "CSoundScript.h"

CPlyMagic_Arrow::CPlyMagic_Arrow()
	: m_vAttackDir{}
	, m_pArrow(nullptr)
{
}

CPlyMagic_Arrow::~CPlyMagic_Arrow()
{
}

void CPlyMagic_Arrow::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::ARROW, false);
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.04f, 0.04f, 0.04f);
	GetOwner()->GetChild()[1]->Transform()->SetRelativeRot(XM_PI / 2.f, XM_PI, XM_PI / 2.f);
	GetOwner()->GetChild()[1]->Transform()->SetRelativePos(Vec3(0.f, 1.f, 1.f));

	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Player\\ArrowCharge.ogg", 1, 0.1f);
}

void CPlyMagic_Arrow::tick()
{
	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// �������� �����ϴٸ� Idle�� ���ư��� ��.
		if (1 > GetOwnerScript()->GetStat().Energy)
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");			
		}
		else if (nullptr == m_pArrow)
		{
			// Player ���׷��̵� ��ġ�� ������ ����� ���� Bomb�� ������������ ����.
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 20.f;
			m_pArrow = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\Arrow.prefab", (int)LAYER::PLAYERPROJECTILE, vSpawnPos);
			m_pArrow->Transform()->SetRelativeScale(Vec3(0.45f));
			m_pArrow->Transform()->SetRelativeRot(m_vAttackDir);
			m_pArrow->Transform()->SetRelativePos(vSpawnPos);
		}
		else if (KEY_RELEASE(KEY::RBTN))
		{
			// ���ݿ� ���� ������ �Ҹ�
			Stat CurStat = GetOwnerScript()->GetStat();
			CurStat.Energy -= 1;
			GetOwnerScript()->SetStat(CurStat);

			// Player ���׷��̵� ��ġ�� ������ ����� ���� Arrow�� ������������ ����.
			float fDamage = GetOwnerScript()->GetStat().Spell_Power * (1.f + 0.3f * GetOwner()->GetScript<CPlayerScript>()->GetUpgrade(PLAYER_UPGRADE::Magic));
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 20.f;
			m_pArrow->Transform()->SetRelativeRot(m_vAttackDir);
			m_pArrow->Transform()->SetRelativeScale(Vec3(0.8f));
			m_pArrow->SetLifeSpan(2.f);

			m_pArrow->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);

			m_pArrow->GetScript<CMagic_ArrowScript>()->SetDir(vDir);
			m_pArrow->GetScript<CMagic_ArrowScript>()->SetStartPos(vSpawnPos);
			m_pArrow->GetScript<CMagic_ArrowScript>()->SetDamage(fDamage);

			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");

			CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
			Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Player\\ArrowFire.ogg", 1, 0.1f);
		}
		else
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 20.f;
			CalcDir();
			m_pArrow->Transform()->SetRelativeRot(m_vAttackDir);
			m_pArrow->Transform()->SetRelativePos(vSpawnPos);
		}
	}
	else
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
}

void CPlyMagic_Arrow::Exit()
{
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	m_pArrow = nullptr;
}

void CPlyMagic_Arrow::CalcDir()
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	m_vAttackDir = Vec3(XM_2PI - XM_PI * 1.5f,fRot, XM_2PI);
}
