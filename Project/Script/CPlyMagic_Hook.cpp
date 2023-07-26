#include "pch.h"
#include "CPlyMagic_Hook.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlyMagic_Hooking.h"
#include "CPlayerScript.h"
#include "CMagic_HookScript.h"

CPlyMagic_Hook::CPlyMagic_Hook()
	: m_fMagicChargeTime(0.f)
{
}

CPlyMagic_Hook::~CPlyMagic_Hook()
{
}

void CPlyMagic_Hook::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
	m_fMagicChargeTime = 0.01f;
}

void CPlyMagic_Hook::tick()
{
	// 갈고리를 걸었다면 Hooking으로 전환하고 갈고리가 걸린 곳의 위치를 지정
	if (m_bHooked)
	{	
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Hooking");
		CPlyMagic_Hooking* pHookingState = (CPlyMagic_Hooking*)GetOwnerScript()->FindState(L"Hooking");
		pHookingState->SetHookedPos(m_vHookPos);
	}

	// 차지 중에는 방향전환 자유롭게
	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}
	m_fMagicChargeTime -= DT;
	// 차지시간이 끝난 후에 우클릭을 해제했다면 투사체 발사
	if (m_fMagicChargeTime <= 0.f)
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			CLevelSaveLoadInScript script;
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 40.f;
			CGameObject* pHook = script.SpawnandReturnPrefab(L"prefab\\Hook.prefab", 4, vSpawnPos, 3.f);
			pHook->GetScript<CMagic_HookScript>()->m_pOwner = this;
			pHook->Rigidbody()->SetGravityVelocityLimit(800.f);
			pHook->Rigidbody()->SetVelocity(vDir * 300000.f);
			pHook->Transform()->SetRelativeRot(m_vAttackDir);

			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
	// 차지시간 전에 해제했다면 Idle로
	else
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
}

void CPlyMagic_Hook::Exit()
{
}

void CPlyMagic_Hook::CalcDir()
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	m_vAttackDir = Vec3(XM_2PI - XM_PI * 1.5f, fRot, XM_2PI);
}