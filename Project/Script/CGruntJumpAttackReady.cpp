#include "pch.h"
#include "CGruntJumpAttackReady.h"
#include "CGruntScript.h"

void CGruntJumpAttackReady::Enter()
{
	GetOwner()->Animator3D()->Play(11, false);
}

void CGruntJumpAttackReady::tick()
{
	// �ִϸ��̼��� ������ NailAttack�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"JumpAttack");
}

void CGruntJumpAttackReady::Exit()
{
}

CGruntJumpAttackReady::CGruntJumpAttackReady()
{
}

CGruntJumpAttackReady::~CGruntJumpAttackReady()
{
}
