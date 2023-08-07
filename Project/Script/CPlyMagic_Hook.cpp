#include "pch.h"
#include "CPlyMagic_Hook.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"
#include "CMagic_HookScript.h"
#include "CPlyMagic_Hooking.h"

CPlyMagic_Hook::CPlyMagic_Hook()
	: m_pHook(nullptr)
	, m_vecChain{}
	, m_vAttackDir{}
	, m_vHookPos{}
	, m_bHooked(false)
	, m_bHookFail(false)
	, m_bThrow(false)
{
	CLevelSaveLoadInScript script;

	if (nullptr == m_pHook)
	{
		m_pHook = script.SpawnandReturnPrefab(L"prefab\\Hook.prefab", (int)LAYER::PLAYERPROJECTILE, Vec3(0.f, 0.f, 0.f));
		m_pHook->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		m_pHook->GetScript<CMagic_HookScript>()->SetOwner(this);
	}
	if (m_vecChain.empty())
	{
		for (int i = 0; i < 80; ++i)
		{
			CGameObject* Chain = script.SpawnandReturnPrefab(L"prefab\\Chain.prefab", (int)LAYER::DEFAULT, Vec3(0.f, 0.f, 0.f));
			Chain->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
			m_vecChain.push_back(Chain);
			m_pHook->GetScript<CMagic_HookScript>()->SetChain(m_vecChain);
		}
	}
}

CPlyMagic_Hook::~CPlyMagic_Hook()
{
}

void CPlyMagic_Hook::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
	// Hooking State에 HookObj 등록
	CPlyMagic_Hooking* pHookingState = (CPlyMagic_Hooking*)GetOwnerScript()->FindState(L"Hooking");
	pHookingState->SetHook(m_pHook);
	pHookingState->SetChain(m_vecChain);
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
		else
			return;
	}
	else
	{
		// 차지 중에는 방향전환 자유롭게
		if (KEY_PRESSED(KEY::RBTN))
		{
			CalcDir();
		}
		else if (KEY_RELEASE(KEY::RBTN))
		{
			m_bThrow = true;
			// 우클릭을 해제하면 갈고리 발사
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 40.f;
			m_vAttackDir.Normalize();
			m_pHook->GetScript<CMagic_HookScript>()->SetStartPos(vSpawnPos);
			m_pHook->GetScript<CMagic_HookScript>()->SetThrowDir(vDir);
			m_pHook->GetScript<CMagic_HookScript>()->SetAttackDir(m_vAttackDir);
			m_pHook->GetScript<CMagic_HookScript>()->Active(true);

			m_pHook->Transform()->SetRelativeRot(Vec3(XM_PI / 2.f + m_vAttackDir.x, m_vAttackDir.y, m_vAttackDir.z));
			m_pHook->Collider3D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
			m_pHook->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
		}
	}
}

void CPlyMagic_Hook::Exit()
{
	m_vAttackDir = {};
	m_vHookPos = {};
	m_bHooked = false;
	m_bHookFail = false;
	m_bThrow = false;
	m_pHook->GetScript<CMagic_HookScript>()->Active(false);
}

void CPlyMagic_Hook::FailSnatch()
{
	if(GetOwnerScript()->GetCurState() == GetOwnerScript()->FindState(L"Hook"))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	}
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