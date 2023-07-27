#include "pch.h"
#include "CCrowBossJump.h"
#include "CCrowBossScript.h"

void CCrowBossJump::Enter()
{
	GetOwner()->Animator3D()->Play(9, false);
	m_Dir = GetOwner()->GetScript<CCrowBossScript>()->GetMonsterToPlayerDir();
}

void CCrowBossJump::tick()
{
	Vec3 Velocity = m_Dir;
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Velocity *= fSpeed;
	Velocity.y = 100.f;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	// 애니메이션이 끝난 경우.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Stomp");
	}
}

void CCrowBossJump::Exit()
{
}

CCrowBossJump::CCrowBossJump() 
{
}

CCrowBossJump::~CCrowBossJump()
{
}
