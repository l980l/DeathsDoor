#include "pch.h"
#include "CGruntDeath.h"
#include "CGruntScript.h"

void CGruntDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, false);
}

void CGruntDeath::tick()
{
	// �׷�Ʈ�� ���� �ִϸ��̼��� �־ �ִϸ��̼� ������ �����۹� ȿ�� �ָ� ��.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// �����۹� ȿ�� ����.
	}

	// �����۹� ȿ���� ������ �ƿ� Destroy ���Ѿ���
}

void CGruntDeath::Exit()
{
}

CGruntDeath::CGruntDeath()
{
}

CGruntDeath::~CGruntDeath()
{
}
