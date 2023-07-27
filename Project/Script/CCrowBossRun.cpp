#include "pch.h"
#include "CCrowBossRun.h"
#include "CCrowBossScript.h"

void CCrowBossRun::Enter()
{
	GetOwner()->Animator3D()->Play(14, false);
}

void CCrowBossRun::tick()
{
	// 공격범위 이내에 플레이어가 있으면 NailAttackReady.
	Vec3 PlayerPos = GetOwner()->GetScript<CCrowBossScript>()->GetPlayerPos();
	float fDistance = GetOwner()->GetScript<CCrowBossScript>()->GetPlayerDistance();

	Vec3 Velocity = GetOwner()->GetScript<CCrowBossScript>()->GetMonsterToPlayerDir();
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Velocity *= fSpeed;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	// 애니메이션이 끝난 경우.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// 애니메이션 4번 재생 후 다른 State로
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
