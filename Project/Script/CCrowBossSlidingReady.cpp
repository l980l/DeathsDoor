#include "pch.h"
#include "CCrowBossSlidingReady.h"
#include "CCrowBossScript.h"

void CCrowBossSlidingReady::Enter()
{
	GetOwner()->Animator3D()->Play(4, false);
}

void CCrowBossSlidingReady::tick()
{
	// ���⼭ �罽�� ������ ��. 
	{
		// �罽 �������� CrowBoss�� �ڽ����� ��ߵ�. �׷��� SlidingState���� �θ��� �ڽ� ������Ʈ �߿��� �罽�� �ִ����� Ȯ���� �� ����. 

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
