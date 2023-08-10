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
	m_vDir = m_vHookPos - vPlayerPos;
	m_vDir.Normalize();
	float fDirtoHooked = GetDir(vPlayerPos, m_vHookPos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fDirtoHooked, 0.f);
}

void CPlyMagic_Hooking::tick()
{
	// Player의 위치와 HookPos의 거리와 방향을 구하고
	// 거리가 일정거리보다 크다면 작을 때까지 방향으로 속도를 줌.
	Vec3 vPlayerPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 DifftoHooked = m_vHookPos - vPlayerPos;
	DifftoHooked.y = 0.f;
	if (DifftoHooked.Length() < 30.f)
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	}
	else
	{
		GetOwner()->Rigidbody()->SetGravity(0.f);
		GetOwner()->Rigidbody()->SetVelocity(m_vDir * 400.f);
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
	m_vDir = {};
	m_bAttack = false;
	m_pHook->GetScript<CMagic_HookScript>()->Active(false);
}
