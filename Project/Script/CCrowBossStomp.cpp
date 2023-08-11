#include "pch.h"
#include "CCrowBossStomp.h"
#include "CCrowBossScript.h"

void CCrowBossStomp::Enter()
{
	GetOwner()->Animator3D()->Play(10, false);

	m_Dir = GetOwner()->GetScript<CCrowBossScript>()->GetMonsterToPlayerDir();
	m_fDistance = GetOwner()->GetScript<CCrowBossScript>()->GetPlayerDistance();
}

void CCrowBossStomp::tick()
{
	// �ִϸ��̼� ����ð����� �÷��̾��� ��ġ���� �����ϱ� ���� Velocity.
	Vec3 Velocity = m_Dir * (m_fDistance / GetOwner()->Animator3D()->GetCurClipTimeLength());
	Velocity *= DT;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	// �ִϸ��̼��� ���� ���.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"RightSpin");
	}
}

void CCrowBossStomp::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}

CCrowBossStomp::CCrowBossStomp() :
	m_fDistance(0.f)
{
}

CCrowBossStomp::~CCrowBossStomp()
{
}
