#include "pch.h"
#include "CCrowBossSlidingReady.h"
#include "CCrowBossScript.h"

void CCrowBossSlidingReady::Enter()
{
	GetOwner()->Animator3D()->Play(4, false);
}

void CCrowBossSlidingReady::tick()
{
	// 여기서 사슬을 내뱉어야 함. 
	{
		// 사슬 프리펩은 CrowBoss의 자식으로 줘야됨. 그래야 SlidingState에서 부모의 자식 오브젝트 중에서 사슬이 있는지를 확인할 수 있음. 

		++m_iSlidingCount;
	}

	if (m_iSlidingCount == 1)
	{
		if (GetOwner()->Animator3D()->IsFinish())
		{
			ChangeState(L"Sliding");
		}
	}

	else if (m_iSlidingCount >= 5)
	{
		if (GetOwner()->Animator3D()->IsFinish())
		{
			ChangeState(L"Sliding");
			m_iSlidingCount = 0;
		}
	}
}

void CCrowBossSlidingReady::Exit()
{
}

CCrowBossSlidingReady::CCrowBossSlidingReady()
{
}

CCrowBossSlidingReady::~CCrowBossSlidingReady()
{
}
