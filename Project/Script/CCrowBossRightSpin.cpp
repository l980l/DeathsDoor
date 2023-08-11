#include "pch.h"
#include "CCrowBossRightSpin.h"
#include "CCrowBossScript.h"

void CCrowBossRightSpin::Enter()
{
	GetOwner()->Animator3D()->Play(12, false);
}

void CCrowBossRightSpin::tick()
{
	// Player ����
	GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(true);

	if (GetOwner()->Animator3D()->IsFinish())
	{
		// ���� ����. �޸���, ����, �罽.
		srand(time(0));
		int iRandom = rand() % 3;

		// �޸���
		if (iRandom == 0)
		{
			GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(true);
			ChangeState(L"Run");
		}
		// ����
		else if (iRandom == 1)
		{
			GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(false);
			ChangeState(L"Jump");
		}
		// �罽
		else if (iRandom == 2)
		{
			Vec3 vPlayerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
			Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDiff = vPlayerPos - vCurPos;
			vDiff.y = 0.f;			

			if (vDiff.Length() < 400.f)
			{
				GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(true);
				ChangeState(L"Run");
			}

			GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(false);
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
