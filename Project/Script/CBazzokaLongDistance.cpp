#include "pch.h"
#include "CBazzokaLongDistance.h"
#include "CBazookaScript.h"

void CBazzokaLongDistance::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);
}

void CBazzokaLongDistance::tick()
{
	// �ִϸ��̼��� ������ Move�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Move");
}

void CBazzokaLongDistance::Exit()
{
}

CBazzokaLongDistance::CBazzokaLongDistance()
{
}

CBazzokaLongDistance::~CBazzokaLongDistance()
{
}
