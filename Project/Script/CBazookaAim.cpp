#include "pch.h"
#include "CBazookaAim.h"
#include "CBazookaScript.h"

void CBazookaAim::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
}

void CBazookaAim::tick()
{
	// ���� �߿� �÷��̾ �ʹ� �����ٸ� �������ų�, ���� ������ �ؾ� �Ѵ�. 
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();

	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());

	if (fDistance < fDistance < GetOwner()->GetScript<CBazookaScript>()->GetRunAwayRange())
	{
		ChangeState(L"Move");
	}
	
	else
	{
		m_fAimTime += DT;

		// ���� �ð� �̻� ���� �� �߻�.
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
