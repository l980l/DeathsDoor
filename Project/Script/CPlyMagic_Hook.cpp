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
	// ������ �ɾ��ٸ� Hooking���� ��ȯ�ϰ� ������ �ɸ� ���� ��ġ�� ����
	if (m_bHooked)
	{	
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Hooking");
		CPlyMagic_Hooking* pHookingState = (CPlyMagic_Hooking*)GetOwnerScript()->FindState(L"Hooking");
		pHookingState->SetHookedPos(m_vHookPos);
	}

	// ���� �߿��� ������ȯ �����Ӱ�
	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}
	m_fMagicChargeTime -= DT;
	// �����ð��� ���� �Ŀ� ��Ŭ���� �����ߴٸ� ����ü �߻�
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
	// �����ð� ���� �����ߴٸ� Idle��
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