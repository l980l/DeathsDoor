#include "pch.h"
#include "CBazzokaMelee.h"
#include "CBazookaScript.h"

void CBazzokaMelee::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);
}

void CBazzokaMelee::tick()
{
	// �ִϸ��̼��� ������ Move�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Move");
}

void CBazzokaMelee::Exit()
{
	// ���� �浹ü �����. 
}

CBazzokaMelee::CBazzokaMelee()
{
}

CBazzokaMelee::~CBazzokaMelee()
{
}
