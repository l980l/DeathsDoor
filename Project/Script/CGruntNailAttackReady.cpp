#include "pch.h"
#include "CGruntNailAttackReady.h"
#include "CGruntScript.h"

void CGruntNailAttackReady::Enter()
{
	GetOwner()->Animator3D()->Play(2, false);
}

void CGruntNailAttackReady::tick()
{
	// �ִϸ��̼��� ������ NailAttack�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"NailAttack");
}

void CGruntNailAttackReady::Exit()
{
}

CGruntNailAttackReady::CGruntNailAttackReady()
{
}

CGruntNailAttackReady::~CGruntNailAttackReady()
{
}
