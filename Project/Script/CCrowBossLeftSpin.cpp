#include "pch.h"
#include "CCrowBossLeftSpin.h"
#include "CCrowBossScript.h"

void CCrowBossLeftSpin::Enter()
{
	GetOwner()->Animator3D()->Play(8, true);
}

void CCrowBossLeftSpin::tick()
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
