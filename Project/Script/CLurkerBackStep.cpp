#include "pch.h"
#include "CLurkerBackStep.h"
#include "CLurkerScript.h"

void CLurkerBackStep::Enter()
{
	GetOwner()->Animator3D()->Play(4, false);
}

void CLurkerBackStep::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	if (CurRatio <= 0.5f)
	{
		Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
		Velocity *= -20.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	else
	{
		Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
		Velocity *= 20.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	// 애니메이션이 끝나면 Notify로 다시 변경.
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
