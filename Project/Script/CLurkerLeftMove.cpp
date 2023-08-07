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

	// �÷��̾ �������� �������� �̵�.
	Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Velocity *= fSpeed;
	swap(Velocity.x, Velocity.z);
	Velocity.z *= -1.f;

	GetOwner()->Rigidbody()->SetVelocity(Velocity);

	// ���� �ð� ���� �̵��ϰ� ��.
	if (m_fTime > 1.f)
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
		ChangeState(L"Notify");
	}
}

void CLurkerLeftMove::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
	m_fTime = 0.f;
}

CLurkerLeftMove::CLurkerLeftMove() :
	m_fTime(0.f)
{
}

CLurkerLeftMove::~CLurkerLeftMove()
{
}
