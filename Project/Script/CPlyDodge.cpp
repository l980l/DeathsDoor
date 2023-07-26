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
	Vec3 Dir = Vec3(0.f, 0.f, 0.f);

	if(!(KEY_PRESSED(KEY::W)) || !(KEY_PRESSED(KEY::A)) || !(KEY_PRESSED(KEY::S)) || !(KEY_PRESSED(KEY::D)))
	{
		Vec3 vCurDir = GetOwner()->Transform()->GetXZDir();
		Dir = Vec3(vCurDir.x, 0.f, vCurDir.z);
	}
	else 
	{
		if (KEY_PRESSED(KEY::W))
		{
			Dir.z = 1.f;
		}
		if (KEY_PRESSED(KEY::A))
		{
			Dir.z = -1.f;
		}
		if (KEY_PRESSED(KEY::S))
		{
			Dir.x = -1.f;
		}
		if (KEY_PRESSED(KEY::D))
		{
			Dir.x = 1.f;
		}
	}

	Dir.Normalize();
	GetOwner()->Rigidbody()->SetVelocityLimit(_fSpeed * 2.f);
	GetOwner()->Rigidbody()->SetVelocity(Dir * _fSpeed * 1000.f);
}
