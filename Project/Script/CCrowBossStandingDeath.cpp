#include "pch.h"
#include "CCrowBossStandingDeath.h"
#include "CCrowBossScript.h"

void CCrowBossStandingDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, true);
}

void CCrowBossStandingDeath::tick()
{
}

void CCrowBossStandingDeath::Exit()
{
}

CCrowBossStandingDeath::CCrowBossStandingDeath()
{
}

CCrowBossStandingDeath::~CCrowBossStandingDeath()
{
}
