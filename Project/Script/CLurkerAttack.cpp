#include "pch.h"
#include "CLurkerAttack.h"
#include "CLurkerScript.h"

void CLurkerAttack::Enter()
{
	GetOwner()->Animator3D()->Play(5, false);

	// ���� ������ ó������ �����ؾ� ��. 
	m_Dir = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
	GetOwner()->GetScript<CLurkerScript>()->SetStarePlayer(false);
}

void CLurkerAttack::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	// ���� ������� �ִϸ��̼��� ������� ���� �� ��� �÷��̾�� ����. �׵ڷ� �ӵ��� �ٽ� �پ�� ���ڸ��� ����� ��.
	if (CurRatio >= 0.5f)
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * 10.f;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	// �ִϸ��̼��� ������ Notify�� �ٽ� ����.
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
