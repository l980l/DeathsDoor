#include "pch.h"
#include "CCrowBossRightSpin.h"
#include "CCrowBossScript.h"

void CCrowBossRightSpin::Enter()
{
	GetOwner()->Animator3D()->Play(12, false);
}

void CCrowBossRightSpin::tick()
{
	// �ִϸ��̼� ���� Player�� �ٶ󺸵��� ȸ���ؾ� ��.


	if (GetOwner()->Animator3D()->IsFinish())
	{
		// ���� ����. �޸���, ����, �罽.
		srand(time(0));
		int iRandom = rand() % 4;

		// �޸���
		if (iRandom == 0)
			ChangeState(L"Run");
		// ����
		else if (iRandom == 1)
			ChangeState(L"Jump");
		// �罽
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
