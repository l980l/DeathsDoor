#include "pch.h"
#include "CGruntDeath.h"
#include "CGruntScript.h"

void CGruntDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, false);
}

void CGruntDeath::tick()
{
	// 그런트는 데스 애니메이션이 있어서 애니메이션 끝나면 페이퍼번 효과 주면 됨.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// 페이퍼번 효과 시작.
	}

	// 페이퍼번 효과가 끝나면 아예 Destroy 시켜야지
}

void CGruntDeath::Exit()
{
}

CGruntDeath::CGruntDeath()
{
}

CGruntDeath::~CGruntDeath()
{
}
