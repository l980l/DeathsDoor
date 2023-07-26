#include "pch.h"
#include "CLurkerNotify.h"
#include "CLurkerScript.h"

void CLurkerNotify::Enter()
{
	// AnimClip 이름은 ReadyAction임
	GetOwner()->Animator3D()->Play(1, false);
	GetOwner()->GetScript<CLurkerScript>()->SetStarePlayer(false);
}

void CLurkerNotify::tick()
{
	// 이미 Notify 행동을 한적이 있다면 다른 상태로.
	if (m_bNotifyAnimEnd)
	{
		Vec3 PlayerPos = GetOwner()->GetScript<CLurkerScript>()->GetPlayerPos();
		float fDistance = GetOwner()->GetScript<CLurkerScript>()->GetPlayerDistance();

		// 공격 범위에 들어온 경우. 난수를 생성해서 4가지 패턴 중 하나를 선택한다. 
		if (fDistance < GetOwner()->GetScript<CLurkerScript>()->GetAttackRange())
		{
			// 너무 가까우면 백스텝.
			if (fDistance < GetOwner()->GetScript<CLurkerScript>()->GetBackStepRange())
			{
				ChangeState(L"BackStep");
			}

			else
			{
				// Player 응시
				GetOwner()->GetScript<CLurkerScript>()->SetStarePlayer(true);

				srand(time(0));
				int iRandom = rand() % 4;

				// 무조건 이전 패턴과 다른 패턴이 나오도록 하기.
				if (m_iPrevPattern == iRandom)
				{
					if (m_iPrevPattern == 3)
						iRandom = 0;

					else
						++iRandom;
				}

				m_iPrevPattern = iRandom;

				if (iRandom == 0)
					ChangeState(L"Attack");
				else if (iRandom == 1)
					ChangeState(L"BackStep");
				else if (iRandom == 2)
					ChangeState(L"LeftMove");
				else if (iRandom == 3)
					ChangeState(L"RightMove");
			}
		}

		else
			ChangeState(L"Trace");
	}

	// 현재 진행중인 ReadyAction 애니메이션이 끝났다면 m_bNotifyAnimEnd를 true로 변경.
	else
	{
		if (GetOwner()->Animator3D()->IsFinish())
			m_bNotifyAnimEnd = true;

		// 애니메이션 재생 시간 동안 플레이어를 바라보도록 회전해야 함.
	}
}

void CLurkerNotify::Exit()
{
}

CLurkerNotify::CLurkerNotify() :
	m_bNotifyAnimEnd(false)
	, m_iPrevPattern(-1)
{
}

CLurkerNotify::~CLurkerNotify()
{
}
