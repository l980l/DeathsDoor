#include "pch.h"
#include "CPlyMagic_Bomb.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"
#include "CMagic_BombScript.h"
#include <Engine/CPhysXMgr.h>

CPlyMagic_Bomb::CPlyMagic_Bomb()
	: m_vAttackDir{}
	, m_Bomb(nullptr)
{
}

CPlyMagic_Bomb::~CPlyMagic_Bomb()
{
}

void CPlyMagic_Bomb::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB, false);
}

void CPlyMagic_Bomb::tick()
{

	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}

	if (GetOwner()->Animator3D()->IsFinish() && GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::MAGIC_BOMB)
	{
		// ��ź�� ó�� 1���� �����ǰ� �����ߴٸ� �� �Ŀ��� ��ġ�� ������.
		if(nullptr == m_Bomb)
		{
			// Player ���׷��̵� ��ġ�� ������ ����� ���� Bomb�� ������������ ����.
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 120.f, CurPos.z) + vDir * 20.f;
			m_Bomb = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\Bomb.prefab", (int)LAYER::PLAYERPROJECTILE, vSpawnPos);
			CPhysXMgr::GetInst()->SetRigidPos(m_Bomb->Rigidbody()->GetRigidbody(), vSpawnPos);
		}
		 else if (KEY_RELEASE(KEY::RBTN))
		{
			// ��ź �غ� �ִϸ��̼��� �����ٸ� �Ӹ� ���� ��ź�� ������.
			CalcDir();
			// ��ź�� ������ ���¿��� ��Ŭ�� Release�ϸ� ��ź ������ �ִϸ��̼� Play �� ��ź�� �ӵ��� ��.
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB_FINISH, false);

			float fDamage = GetOwnerScript()->GetStat().Spell_Power * (1.f + 0.3f * GetOwner()->GetScript<CPlayerScript>()->GetUpgrade(PLAYER_UPGRADE::Magic));
			fDamage *= 2.5f;
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			m_Bomb->GetScript<CMagic_BombScript>()->SetDamege(fDamage);
			m_Bomb->GetScript<CMagic_BombScript>()->SetDir(vDir);
			m_Bomb->GetScript<CMagic_BombScript>()->SetThrow();
			m_Bomb->SetLifeSpan(3.f);
		}
		 else
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 120.f, CurPos.z) + vDir * 40.f;
			CPhysXMgr::GetInst()->SetRigidPos(m_Bomb->Rigidbody()->GetRigidbody(), vSpawnPos);
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
	m_Bomb = nullptr;
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