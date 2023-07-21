#include "pch.h"
#include "CBazzokaMelee.h"
#include "CBazookaScript.h"

void CBazzokaMelee::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);
}

void CBazzokaMelee::tick()
{
	// 애니메이션이 끝나면 Move로 다시 변경.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Move");
}

void CBazzokaMelee::Exit()
{
	// 공격 충돌체 만들기. 
}

CBazzokaMelee::CBazzokaMelee()
{
}

CBazzokaMelee::~CBazzokaMelee()
{
}
