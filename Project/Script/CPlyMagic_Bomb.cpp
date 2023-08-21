#include "pch.h"
#include "CPlyMagic_Bomb.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"
#include "CMagic_BombScript.h"
#include <Engine/CPhysXMgr.h>
#include "CSoundScript.h"
#include "CUIMgr.h"

CPlyMagic_Bomb::CPlyMagic_Bomb()
	: m_vAttackDir{}
	, m_pBomb(nullptr)
{
}

CPlyMagic_Bomb::~CPlyMagic_Bomb()
{
}

void CPlyMagic_Bomb::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB, false);

	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Player\\BombCharge.ogg", 1, 1.f);
}

void CPlyMagic_Bomb::tick()
{

	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}

	if (GetOwner()->Animator3D()->IsFinish() && GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::MAGIC_BOMB)
	{
		// �������� �����ϴٸ� Idle�� ���ư��� ��.
		if (2 > GetOwnerScript()->GetStat().MP)
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
		// ��ź�� ó�� 1���� �����ǰ� �����ߴٸ� �� �Ŀ��� ��ġ�� ������.
		else if(nullptr == m_pBomb)
		{
			// Player ���׷��̵� ��ġ�� ������ ����� ���� Bomb�� ������������ ����.
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 120.f, CurPos.z) + vDir * 20.f;
			m_pBomb = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\Bomb.prefab", (int)LAYER::PLAYERPROJECTILE, vSpawnPos);
			m_pBomb->Rigidbody()->SetRigidPos(vSpawnPos);
		}
		 else if (KEY_RELEASE(KEY::RBTN))
		{
			// ���ݿ� ���� ������ �Ҹ�
			Stat CurStat = GetOwnerScript()->GetStat();
			CurStat.MP -= 2;
			GetOwnerScript()->SetStat(CurStat);

			// ��ź �غ� �ִϸ��̼��� �����ٸ� �Ӹ� ���� ��ź�� ������.
			CalcDir();
			// ��ź�� ������ ���¿��� ��Ŭ�� Release�ϸ� ��ź ������ �ִϸ��̼� Play �� ��ź�� �ӵ��� ��.
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB_FINISH, false);

			float fDamage = GetOwnerScript()->GetStat().Spell_Power * (1.f + 0.3f * GetOwner()->GetScript<CPlayerScript>()->GetUpgrade(PLAYER_UPGRADE::MAGIC));
			fDamage *= 2.5f;
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			m_pBomb->GetScript<CMagic_BombScript>()->SetDamege(fDamage);
			m_pBomb->GetScript<CMagic_BombScript>()->SetDir(vDir);
			m_pBomb->GetScript<CMagic_BombScript>()->SetThrow();
			m_pBomb->GetScript<CMagic_BombScript>()->SetCollidable();
			m_pBomb->SetLifeSpan(2.f);

			CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
			Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Player\\BombFire.ogg", 1, 1.f);
		}
		 else
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 120.f, CurPos.z) + vDir * 40.f;
			m_pBomb->Rigidbody()->SetRigidPos(vSpawnPos);
		}
	}
	else if (GetOwner()->Animator3D()->IsFinish() && GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::MAGIC_BOMB_FINISH)
	{
		// ��ź�� ������ ���� �ִϸ��̼��� �����ٸ� Idle�� ��ȯ
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	}
	else
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}

}

void CPlyMagic_Bomb::Exit()
{
	m_pBomb = nullptr;
}

void CPlyMagic_Bomb::CalcDir()
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	m_vAttackDir = Vec3(XM_2PI - XM_PI * 1.5f, fRot, XM_2PI);
}