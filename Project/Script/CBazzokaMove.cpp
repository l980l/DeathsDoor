#include "pch.h"
#include "CBazzokaMove.h"
#include "CBazookaScript.h"

void CBazzokaMove::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CBazzokaMove::tick()
{
}

void CBazzokaMove::Exit()
{
}

CBazzokaMove::CBazzokaMove()
{
}

CBazzokaMove::~CBazzokaMove()
{
}
