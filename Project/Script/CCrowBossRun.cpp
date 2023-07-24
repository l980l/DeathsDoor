#include "pch.h"
#include "CCrowBossRun.h"
#include "CCrowBossScript.h"

void CCrowBossRun::tick()
{
	GetOwner()->Animator3D()->Play(14, true);
}

void CCrowBossRun::Enter()
{
}

void CCrowBossRun::Exit()
{
}

CCrowBossRun::CCrowBossRun()
{
}

CCrowBossRun::~CCrowBossRun()
{
}
