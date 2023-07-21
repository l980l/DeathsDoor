#include "pch.h"
#include "CBazookaAim.h"
#include "CBazookaScript.h"

void CBazookaAim::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
}

void CBazookaAim::tick()
{
}

void CBazookaAim::Exit()
{
}

CBazookaAim::CBazookaAim()
{
}

CBazookaAim::~CBazookaAim()
{
}
