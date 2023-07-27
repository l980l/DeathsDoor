#include "pch.h"
#include "CGruntNailAttack.h"
#include "CGruntScript.h"

void CGruntNailAttack::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);

	// 공격 방향은 처음에만 지정해야 함. 
	m_Dir = GetOwner()->GetScript<CGruntScript>()->GetMonsterToPlayerDir();
}

void CGruntNailAttack::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	// 현재 재생중인 애니메이션이 어느정도 진행 된 경우 플레이어로 돌진. 그뒤로 속도가 다시 줄어들어서 제자리에 멈춰야 함.
	if (CurRatio >= 0.5f && CurRatio <= 0.9f)
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * 5.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	else if (CurRatio > 0.9f)
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * -20.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	// 애니메이션이 끝나면 Run2로 다시 변경.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Run2");
}

void CGruntNailAttack::Exit()
{
	m_fTime = 0.f;
}

CGruntNailAttack::CGruntNailAttack() :
	m_fTime(0.f)
{
}

CGruntNailAttack::~CGruntNailAttack()
{
}
