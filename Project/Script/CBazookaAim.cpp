#include "pch.h"
#include "CBazookaAim.h"
#include "CBazookaScript.h"

void CBazookaAim::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
}

void CBazookaAim::tick()
{
	// 조준 중에 플레이어가 너무 가깝다면 도망가거나, 근접 공격을 해야 한다. 
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();

	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());

	if (fDistance < fDistance < GetOwner()->GetScript<CBazookaScript>()->GetRunAwayRange())
	{
		ChangeState(L"Move");
	}
	
	else
	{
		m_fAimTime += DT;

		// 일정 시간 이상 조준 후 발사.
		if (m_fAimTime >= 2.f)
			ChangeState(L"LongDistance");
	}
}

void CBazookaAim::Exit()
{
	m_fAimTime = 0.f;
}

CBazookaAim::CBazookaAim() :
	m_fAimTime(0.f)
{
}

CBazookaAim::~CBazookaAim()
{
}
