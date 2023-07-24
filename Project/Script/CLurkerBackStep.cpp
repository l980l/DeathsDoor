#include "pch.h"
#include "CLurkerBackStep.h"
#include "CLurkerScript.h"

void CLurkerBackStep::Enter()
{
	GetOwner()->Animator3D()->Play(4, false);
	m_Dir = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
}

void CLurkerBackStep::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	if (CurRatio <= 0.5f)
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * -5.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	else
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * 5.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	// �ִϸ��̼��� ������ Notify�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Notify");
}

void CLurkerBackStep::Exit()
{
	m_fTime = 0.f;
}

CLurkerBackStep::CLurkerBackStep() :
	m_fTime(0.f)
{
}

CLurkerBackStep::~CLurkerBackStep()
{
}
