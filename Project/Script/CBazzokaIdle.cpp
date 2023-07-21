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
	
	// Detect ���¶�� Move ���·� ��ȯ.
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
