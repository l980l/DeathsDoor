#include "pch.h"
#include "CBazzokaLongDistance.h"
#include "CBazookaScript.h"

void CBazzokaLongDistance::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);
}

void CBazzokaLongDistance::tick()
{
	// 애니메이션이 끝나면 Move로 다시 변경.
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
