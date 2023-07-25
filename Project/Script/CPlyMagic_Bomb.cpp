#include "pch.h"
#include "CPlyMagic_Bomb.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"

CPlyMagic_Bomb::CPlyMagic_Bomb()
	: m_fMagicChargeTime(0.f)
{
}

CPlyMagic_Bomb::~CPlyMagic_Bomb()
{
}

void CPlyMagic_Bomb::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB, false);
	m_fMagicChargeTime = 1.5f;
}

void CPlyMagic_Bomb::tick()
{

	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}
	m_fMagicChargeTime -= DT;
	if (m_fMagicChargeTime <= 0.f)
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			CLevelSaveLoadInScript script;
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 40.f;
			CGameObject* pArrow = script.SpawnandReturnPrefab(L"prefab\\Bomb.prefab", 4, vSpawnPos, 3.f);
			pArrow->Rigidbody()->SetGravityVelocityLimit(1200.f);
			pArrow->Rigidbody()->AddForce(vDir * 30000.f);
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

void CPlyMagic_Bomb::Exit()
{
	m_fMagicChargeTime = 0.f;
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