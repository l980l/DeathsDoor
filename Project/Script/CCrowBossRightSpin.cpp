#include "pch.h"
#include "CCrowBossRightSpin.h"
#include "CCrowBossScript.h"

void CCrowBossRightSpin::Enter()
{
	GetOwner()->Animator3D()->Play(12, false);
}

void CCrowBossRightSpin::tick()
{
	// 애니메이션 동안 Player를 바라보도록 회전해야 함.


	if (GetOwner()->Animator3D()->IsFinish())
	{
		// 패턴 선택. 달리기, 점프, 사슬.
		srand(time(0));
		int iRandom = rand() % 4;

		// 달리기
		if (iRandom == 0)
			ChangeState(L"Run");
		// 점프
		else if (iRandom == 1)
			ChangeState(L"Jump");
		// 사슬
		else if (iRandom == 2)
			ChangeState(L"SlidingReady");
	}
}

void CCrowBossRightSpin::Exit()
{
}

CCrowBossRightSpin::CCrowBossRightSpin()
{
}

CCrowBossRightSpin::~CCrowBossRightSpin()
{
}
