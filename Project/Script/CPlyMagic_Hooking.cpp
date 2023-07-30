#include "pch.h"
#include "CPlyMagic_Hooking.h"
#include "CPlayerScript.h"
#include "CMagic_HookScript.h"

CPlyMagic_Hooking::CPlyMagic_Hooking()
	: m_vHookPos{}
	, m_bAttack(false)
	, m_pHook(nullptr)
{
}

CPlyMagic_Hooking::~CPlyMagic_Hooking()
{
}

void CPlyMagic_Hooking::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOKING, true);

	// 날아가는 방향으로 Dir 설정
	Vec3 vPlayerPos = GetOwner()->Transform()->GetWorldPos();
	float fDirtoHooked = GetDir(vPlayerPos, m_vHookPos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fDirtoHooked, 0.f);
	GetOwner()->Rigidbody()->SetVelocityLimit(1500.f);
}

void CPlyMagic_Hooking::tick()
{
	Vec3 vPlayerPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 DifftoHooked = m_vHookPos - vPlayerPos;
	if (abs(DifftoHooked.x) + abs(DifftoHooked.z) < 100.f)
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	else
	{
		DifftoHooked.Normalize();
		GetOwner()->Rigidbody()->SetVelocity(Vec3(DifftoHooked.x * 30000.f, 0.f, DifftoHooked.z * 30000.f));
	}

	if (!m_bAttack)
	{
		if(KEY_PRESSED(KEY::LBTN))
		{
			// 공격모션과 함께 대시공격 프리펩 생성
		}
	}
}

void CPlyMagic_Hooking::Exit()
{
	m_vHookPos = {};
	m_bAttack = false;
	m_pHook->GetScript<CMagic_HookScript>()->Active(false);
}
