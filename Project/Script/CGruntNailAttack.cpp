#include "pch.h"
#include "CGruntNailAttack.h"
#include "CGruntScript.h"

void CGruntNailAttack::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);

	// ���� ������ ó������ �����ؾ� ��. 
	m_Dir = GetOwner()->GetScript<CGruntScript>()->GetMonsterToPlayerDir();
}

void CGruntNailAttack::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	// ���� ������� �ִϸ��̼��� ������� ���� �� ��� �÷��̾�� ����. �׵ڷ� �ӵ��� �ٽ� �پ�� ���ڸ��� ����� ��.
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

	// �ִϸ��̼��� ������ Run2�� �ٽ� ����.
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
