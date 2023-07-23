#include "pch.h"
#include "CLurkerLeftMove.h"
#include "CLurkerScript.h"

void CLurkerLeftMove::Enter()
{
	GetOwner()->Animator3D()->Play(7, true);
}

void CLurkerLeftMove::tick()
{
	m_fTime += DT;

	// 플레이어를 기준으로 왼쪽으로 이동.
	Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
	Velocity *= 10.f;
	swap(Velocity.x, Velocity.z);
	Velocity.z *= -1.f;

	GetOwner()->Rigidbody()->SetVelocity(Velocity);

	// 일정 시간 동안 이동하고 끝.
	if (m_fTime > 2.f)
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
		ChangeState(L"Notify");
	}
}

void CLurkerLeftMove::Exit()
{
	m_fTime = 0.f;
}

CLurkerLeftMove::CLurkerLeftMove() :
	m_fTime(0.f)
{
}

CLurkerLeftMove::~CLurkerLeftMove()
{
}
