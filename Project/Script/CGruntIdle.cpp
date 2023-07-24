#include "pch.h"
#include "CGruntIdle.h"
#include "CGruntScript.h"

void CGruntIdle::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
}

void CGruntIdle::tick()
{
	CGameObject* pPlayer = GetOwner()->GetScript<CGruntScript>()->GetPlayer();

	// Detect ���¶�� Notify ���·� ��ȯ.
	if (GetOwner()->GetScript<CGruntScript>()->GetDetect())
	{
		ChangeState(L"Run2");
	}
}

void CGruntIdle::Exit()
{
}

CGruntIdle::CGruntIdle()
{
}

CGruntIdle::~CGruntIdle()
{
}
