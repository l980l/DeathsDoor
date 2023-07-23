#include "pch.h"
#include "CLurkerRightMove.h"
#include "CLurkerScript.h"

void CLurkerRightMove::Enter()
{
	GetOwner()->Animator3D()->Play(8, true);
}

void CLurkerRightMove::tick()
{
	m_fTime += DT;

	// �÷��̾ �������� �������� �̵�.
	Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
	Velocity *= 10.f;
	swap(Velocity.x, Velocity.z);
	Velocity.x *= -1.f;

	GetOwner()->Rigidbody()->SetVelocity(Velocity);

	// ���� �ð� ���� �̵��ϰ� ��.
	if (m_fTime > 2.f)
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
		ChangeState(L"Notify");
	}
}

void CLurkerRightMove::Exit()
{
	m_fTime = 0.f;
}

CLurkerRightMove::CLurkerRightMove() :
	m_fTime(0.f)
{
}

CLurkerRightMove::~CLurkerRightMove()
{
}
