#include "pch.h"
#include "CLurkerNotify.h"
#include "CLurkerScript.h"

void CLurkerNotify::Enter()
{
	// AnimClip �̸��� ReadyAction��
	GetOwner()->Animator3D()->Play(1, false);
}

void CLurkerNotify::tick()
{
	// �̹� Notify �ൿ�� ������ �ִٸ� �ٸ� ���·�.
	if (m_bNotifyAnimEnd)
	{
		Vec3 PlayerPos = GetOwner()->GetScript<CLurkerScript>()->GetPlayerPos();
		float fDistance = GetOwner()->GetScript<CLurkerScript>()->GetPlayerDistance();

		// ���� ������ ���� ���. ������ �����ؼ� 4���� ���� �� �ϳ��� �����Ѵ�. 
		if (fDistance < GetOwner()->GetScript<CLurkerScript>()->GetAttackRange())
		{
			srand(time(0));
			int iRandom = rand() % 4;

			if(iRandom == 0)
				ChangeState(L"Attack");
			else if (iRandom == 1)
				ChangeState(L"BackStep");
			else if (iRandom == 2)
				ChangeState(L"LeftMove");
			else if (iRandom == 3)
				ChangeState(L"RightMove");
		}

		else
			ChangeState(L"Trace");
	}

	// ���� �������� ReadyAction �ִϸ��̼��� �����ٸ� m_bNotifyAnimEnd�� true�� ����.
	else
	{
		if (GetOwner()->Animator3D()->IsFinish())
			m_bNotifyAnimEnd = true;

		// �ִϸ��̼� ��� �ð� ���� �÷��̾ �ٶ󺸵��� ȸ���ؾ� ��.
	}
}

void CLurkerNotify::Exit()
{
}

CLurkerNotify::CLurkerNotify() :
	m_bNotifyAnimEnd(false)
{
}

CLurkerNotify::~CLurkerNotify()
{
}
