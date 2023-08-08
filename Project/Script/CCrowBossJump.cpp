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
	Velocity *= fSpeed * 30.f * DT;
	Velocity.y = fSpeed * 30.f * DT;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	// �ִϸ��̼��� ���� ���.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Stomp");
	}
}

void CCrowBossJump::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}

CCrowBossJump::CCrowBossJump() 
{
}

CCrowBossJump::~CCrowBossJump()
{
}
