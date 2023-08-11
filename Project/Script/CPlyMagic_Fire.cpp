#include "pch.h"
#include "CPlyMagic_Fire.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"

CPlyMagic_Fire::CPlyMagic_Fire()
{
}

CPlyMagic_Fire::~CPlyMagic_Fire()
{
}

void CPlyMagic_Fire::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_FIRE, false);
}

void CPlyMagic_Fire::tick()
{

	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}
	if (GetOwner()->Animator3D()->IsFinish())
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			// Player 업그레이드 수치를 가져와 계수를 곱해 Fire의 최종데미지를 정함.
			float fDamage = GetOwnerScript()->GetStat().Spell_Power * (1.f + 0.3f * GetOwner()->GetScript<CPlayerScript>()->GetUpgrade(PLAYER_UPGRADE::Magic));
			fDamage *= 1.3f;
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 40.f;
			CGameObject* pArrow = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasBulletParticle.prefab", (int)LAYER::PLAYERPROJECTILE, vSpawnPos, 3.f);
			pArrow->Transform()->SetRelativeRot(m_vAttackDir);

			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
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

void CPlyMagic_Fire::Exit()
{
}

void CPlyMagic_Fire::CalcDir()
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	m_vAttackDir = Vec3(XM_2PI - XM_PI * 1.5f, fRot, XM_2PI);
}