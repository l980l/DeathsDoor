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
	Vec3 PlayerPos = GetOwner()->GetScript<CCrowBossScript>()->GetPlayerPos();
	float fDistance = GetOwner()->GetScript<CCrowBossScript>()->GetPlayerDistance();

	Vec3 Velocity = GetOwner()->GetScript<CCrowBossScript>()->GetMonsterToPlayerDir();
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Velocity *= fSpeed;

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
	m_iTime = 0;
}

CCrowBossRun::CCrowBossRun() :
	m_iTime(0)
{
}

CCrowBossRun::~CCrowBossRun()
{
}
