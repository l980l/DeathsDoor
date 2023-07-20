#include "pch.h"
#include "CBazzokaIdle.h"
#include "CBazookaScript.h"

#include <Engine/CTransform.h>

void CBazzokaIdle::Enter()
{
	GetOwner()->Animator3D()->Play(2, true);
}

void CBazzokaIdle::tick()
{
	CGameObject* pPlayer = GetOwner()->GetScript<CBazookaScript>()->GetPlayer();
	
	// Detect 상태라면 Move 상태로 전환.
	if (GetOwner()->GetScript<CBazookaScript>()->GetDetect())
	{
		ChangeState(L"Move");
	}
}

void CBazzokaIdle::Exit()
{
}

CBazzokaIdle::CBazzokaIdle()
{
}

CBazzokaIdle::~CBazzokaIdle()
{
}
