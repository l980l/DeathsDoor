#include "pch.h"
#include "CLurkerAttack.h"
#include "CLurkerScript.h"

void CLurkerAttack::Enter()
{
	GetOwner()->Animator3D()->Play(5, false);
}

void CLurkerAttack::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	// 현재 재생중인 애니메이션이 어느정도 진행 된 경우 플레이어로 돌진. 그뒤로 속도가 다시 줄어들어서 제자리에 멈춰야 함.
	if (CurRatio >= 0.5f && CurRatio <= 0.9f)
	{
		Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
		Velocity *= 10.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	else if (CurRatio > 0.9f)
	{
		Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
		Velocity *= -40.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	// 애니메이션이 끝나면 Notify로 다시 변경.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Notify");
}

void CLurkerAttack::Exit()
{
	m_fTime = 0.f;
}

CLurkerAttack::CLurkerAttack() :
	m_fTime(0.f)
{
}

CLurkerAttack::~CLurkerAttack()
{
}
