#include "pch.h"
#include "CLurkerIdle.h"
#include "CLurkerScript.h"

void CLurkerIdle::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
}

void CLurkerIdle::tick()
{
	CGameObject* pPlayer = GetOwner()->GetScript<CLurkerScript>()->GetPlayer();

	// Detect ���¶�� Notify ���·� ��ȯ.
	if (GetOwner()->GetScript<CLurkerScript>()->GetDetect())
	{
		ChangeState(L"Notify");
	}
}

void CLurkerIdle::Exit()
{
}

CLurkerIdle::CLurkerIdle()
{
}

CLurkerIdle::~CLurkerIdle()
{
}
