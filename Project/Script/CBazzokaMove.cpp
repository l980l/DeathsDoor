#include "pch.h"
#include "CBazzokaMove.h"
#include "CBazookaScript.h"

void CBazzokaMove::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CBazzokaMove::tick()
{
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();

	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());

	// 300 이하면 Melee
	if (fDistance < 300.f)
	{
		ChangeState(L"Melee");
	}

	// 300 ~ 500이면 도망
	else if (fDistance < 1000.f)
	{
		
	}

	// 500 ~ 1500 사이면 Aim
	else if (fDistance<1500.f)
	{
		ChangeState(L"Aim");
	}

	// 1500 이상이면 Trace
	else
	{
		ChangeState(L"Trace");
	}
}

void CBazzokaMove::Exit()
{
}

CBazzokaMove::CBazzokaMove()
{
}

CBazzokaMove::~CBazzokaMove()
{
}
