#include "pch.h"
#include "CPlyMagic_Hook.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlyMagic_Hooking.h"
#include "CPlayerScript.h"
#include "CMagic_HookScript.h"

CPlyMagic_Hook::CPlyMagic_Hook()
	: m_vAttackDir{}
	, m_bHooked(false)
	, m_bHookFail(false)
	, m_vHookPos{}
	, m_bThrow(false)
{
}

CPlyMagic_Hook::~CPlyMagic_Hook()
{
}

void CPlyMagic_Hook::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
	GetOwner()->GetChild()[0]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
}

void CPlyMagic_Hook::tick()
{
	if(m_bThrow)
	{
		// 갈고리를 걸었다면 Hooking으로 전환하고 갈고리가 걸린 곳의 위치를 지정
		if (m_bHooked)
		{
			CPlyMagic_Hooking* pHookingState = (CPlyMagic_Hooking*)GetOwnerScript()->FindState(L"Hooking");
			pHookingState->SetHookedPos(m_vHookPos);
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Hooking");
		}
		else if (m_bHookFail)
		{
			GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
	else
	{
		// 차지 중에는 방향전환 자유롭게
		if (KEY_PRESSED(KEY::RBTN))
		{
			CalcDir();
		}
		if (KEY_RELEASE(KEY::RBTN))
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			CLevelSaveLoadInScript script;
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 40.f;
			CGameObject* pHook = script.SpawnandReturnPrefab(L"prefab\\Hook.prefab", (int)LAYER::PLAYERPROJECTILE, vSpawnPos);
			pHook->GetScript<CMagic_HookScript>()->m_pOwner = this;
			pHook->GetScript<CMagic_HookScript>()->m_vStartPos = CurPos;
			pHook->GetScript<CMagic_HookScript>()->m_vThrownDir = vDir * 300000.f;
			pHook->Collider3D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
			pHook->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
			pHook->Rigidbody()->SetVelocityLimit(2000.f);
			pHook->Rigidbody()->SetFriction(0.f);
			pHook->Rigidbody()->SetMass(1.f);
			pHook->Rigidbody()->SetFrictionScale(1.f);
			pHook->Rigidbody()->SetGravityVelocityLimit(800.f);
			pHook->Rigidbody()->SetVelocity(vDir * 300000.f);
			pHook->Transform()->SetRelativeRot(m_vAttackDir);
			m_bThrow = true;
		}
	}
}

void CPlyMagic_Hook::Exit()
{
	GetOwner()->GetChild()[0]->Transform()->SetRelativeScale(1.f, 1.f, 1.f);
	m_bHooked = false;
	m_bHookFail = false;
	m_vHookPos = {};
	m_bThrow = false;
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