#include "pch.h"
#include "CBazookaAim.h"
#include "CBazookaScript.h"

void CBazookaAim::Enter()
{
	GetOwner()->Animator3D()->Play(0, false);
}

void CBazookaAim::tick()
{
	// ���� �߿� �÷��̾ �ʹ� �����ٸ� �������ų�, ���� ������ �ؾ� �Ѵ�. 
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();

	float fDistance = GetOwner()->GetScript<CBazookaScript>()->GetPlayerDistance();

	if (fDistance < GetOwner()->GetScript<CBazookaScript>()->GetRunAwayRange())
	{
		ChangeState(L"Move");
	}
	
	else if(GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"LongDistance");
	}
}

void CBazookaAim::Exit()
{
}

CBazookaAim::CBazookaAim()
{
}

CBazookaAim::~CBazookaAim()
{
}
