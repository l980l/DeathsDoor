#include "pch.h"
#include "CLurkerDeath.h"
#include "CLurkerScript.h"

void CLurkerDeath::Enter()
{
	GetOwner()->Animator3D()->Play(6, false);
}

void CLurkerDeath::tick()
{
	// ��Ŀ�� ���� �ִϸ��̼��� �־ �ִϸ��̼� ������ �����۹� ȿ�� �ָ� ��.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// �����۹� ȿ�� ����.
	}

	// �����۹� ȿ���� ������ �ƿ� Destroy ���Ѿ���
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
