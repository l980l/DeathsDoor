#include "pch.h"
#include "CCrowBossRun.h"
#include "CCrowBossScript.h"

void CCrowBossRun::Enter()
{
	GetOwner()->Animator3D()->Play(14, false);
}

void CCrowBossRun::tick()
{
	// ���ݹ��� �̳��� �÷��̾ ������ NailAttackReady.
	m_Dir = GetOwner()->GetScript<CCrowBossScript>()->GetMonsterToPlayerDir();

	Vec3 Velocity = m_Dir;
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Velocity *= fSpeed * 30.f * DT;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	// �ִϸ��̼��� ���� ���.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// �ִϸ��̼� 4�� ��� �� �ٸ� State��
		if (m_iTime>=3)
		{
			ChangeState(L"RightSpin");
		}
	
		++m_iTime;
	}
}

void CCrowBossRun::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
	m_iTime = 0;
}

CCrowBossRun::CCrowBossRun() :
	m_iTime(0)
{
}

CCrowBossRun::~CCrowBossRun()
{
}
