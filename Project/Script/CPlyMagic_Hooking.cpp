#include "pch.h"
#include "CPlyMagic_Hooking.h"
#include "CPlayerScript.h"

CPlyMagic_Hooking::CPlyMagic_Hooking()
	: m_vHookPos{}
	, m_bAttack(false)
{
}

CPlyMagic_Hooking::~CPlyMagic_Hooking()
{
}

void CPlyMagic_Hooking::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOKING, true);
	Vec3 vPlayerPos = GetOwner()->Transform()->GetWorldPos();
	float fDirtoHooked = GetDir(vPlayerPos, m_vHookPos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fDirtoHooked, 0.f);
}

void CPlyMagic_Hooking::tick()
{
	Vec3 vPlayerPos = GetOwner()->Transform()->GetWorldPos();
	float fDirtoHooked = GetDir(vPlayerPos, m_vHookPos);
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, fDirtoHooked * 30000, 0.f));

	Vec3 DifftoHooked = vPlayerPos - m_vHookPos;
	if (abs(DifftoHooked.x) + abs(DifftoHooked.z) > 100.f)
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");

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
}
