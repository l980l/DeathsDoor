#include "pch.h"
#include "CPlyDodge.h"
#include "CPlayerScript.h"

CPlyDodge::CPlyDodge()
{
}

CPlyDodge::~CPlyDodge()
{
}

void CPlyDodge::Enter()
{
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Dodge(fSpeed);
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::DODGE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDodge::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
}

void CPlyDodge::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
}

void CPlyDodge::Dodge(float _fSpeed)
{
	Vec3 vCurDir = GetOwner()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	vCurDir.y = 0.f;
	vCurDir.Normalize();
	GetOwner()->Rigidbody()->SetVelocityLimit(_fSpeed * 2.f);
	GetOwner()->Rigidbody()->SetVelocity(vCurDir * _fSpeed * 1000.f);
}

void CPlyDodge::CalcDir()
{
}
