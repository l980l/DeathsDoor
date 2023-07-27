#include "pch.h"
#include "CGruntJumpAttack.h"
#include "CGruntScript.h"

void CGruntJumpAttack::Enter()
{
	GetOwner()->Animator3D()->Play(12, false);

	// 공격 방향은 처음에만 지정해야 함. 
	m_Dir = GetOwner()->GetScript<CGruntScript>()->GetMonsterToPlayerDir();
}

void CGruntJumpAttack::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	if (CurRatio <= 0.5f)
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * 5.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	else
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * -5.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	// 애니메이션이 끝나면 Run2로 다시 변경.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Run2");
}

void CGruntJumpAttack::Exit()
{
	m_fTime = 0.f;
}

CGruntJumpAttack::CGruntJumpAttack() :
	m_fTime(0.f)
{
}

CGruntJumpAttack::~CGruntJumpAttack()
{
}
