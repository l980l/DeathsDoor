#include "pch.h"
#include "CLurkerDeath.h"
#include "CLurkerScript.h"

void CLurkerDeath::Enter()
{
	GetOwner()->Animator3D()->Play(6, false);
}

void CLurkerDeath::tick()
{
	// 럴커는 데스 애니메이션이 있어서 애니메이션 끝나면 페이퍼번 효과 주면 됨.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// 페이퍼번 효과 시작.
	}

	// 페이퍼번 효과가 끝나면 아예 Destroy 시켜야지
}

void CLurkerDeath::Exit()
{
}

CLurkerDeath::CLurkerDeath()
{
}

CLurkerDeath::~CLurkerDeath()
{
}
