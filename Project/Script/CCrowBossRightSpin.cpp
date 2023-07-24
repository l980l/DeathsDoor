#include "pch.h"
#include "CCrowBossRightSpin.h"
#include "CCrowBossScript.h"

void CCrowBossRightSpin::tick()
{
	GetOwner()->Animator3D()->Play(12, true);
}

void CCrowBossRightSpin::Enter()
{
}

void CCrowBossRightSpin::Exit()
{
}

CCrowBossRightSpin::CCrowBossRightSpin()
{
}

CCrowBossRightSpin::~CCrowBossRightSpin()
{
}
