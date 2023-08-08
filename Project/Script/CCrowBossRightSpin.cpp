#include "pch.h"
#include "CCrowBossRightSpin.h"
#include "CCrowBossScript.h"

void CCrowBossRightSpin::Enter()
{
	GetOwner()->Animator3D()->Play(12, false);
}

void CCrowBossRightSpin::tick()
{
	// Player 응시
	GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(true);

	if (GetOwner()->Animator3D()->IsFinish())
	{
		// 패턴 선택. 달리기, 점프, 사슬.
		srand(time(0));
		int iRandom = rand() % 4;

		// 달리기
		if (iRandom == 0)
		{
			GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(false);
			ChangeState(L"Run");
		}
		// 점프
		else if (iRandom == 1)
		{
			GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(false);
			ChangeState(L"Jump");
		}
		// 사슬
		else if (iRandom == 2)
		{
			ChangeState(L"SlidingReady");
		}
	}
}

void CCrowBossRightSpin::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}

CCrowBossRightSpin::CCrowBossRightSpin()
{
}

CCrowBossRightSpin::~CCrowBossRightSpin()
{
}
