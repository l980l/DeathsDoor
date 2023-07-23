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
	if (m_bNotify)
	{

	}

	// ���� �������� ReadyAction �ִϸ��̼��� �����ٸ� m_bNotify�� true�� ����.
	else
	{
		if (GetOwner()->Animator3D()->IsFinish())
			m_bNotify = true;

		// �ִϸ��̼� ��� �ð� ���� �÷��̾ �ٶ󺸵��� ȸ���ؾ� ��.
	}
}

void CLurkerNotify::Exit()
{
}

CLurkerNotify::CLurkerNotify() :
	m_bNotify(false)
{
}

CLurkerNotify::~CLurkerNotify()
{
}
