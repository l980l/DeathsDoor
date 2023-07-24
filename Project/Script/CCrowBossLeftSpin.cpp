#include "pch.h"
#include "CCrowBossLeftSpin.h"
#include "CCrowBossScript.h"

void CCrowBossLeftSpin::tick()
{
	GetOwner()->Animator3D()->Play(8, true);
}

void CCrowBossLeftSpin::Enter()
{
}

void CCrowBossLeftSpin::Exit()
{
}

CCrowBossLeftSpin::CCrowBossLeftSpin()
{
}

CCrowBossLeftSpin::~CCrowBossLeftSpin()
{
}
