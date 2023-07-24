#include "pch.h"
#include "CCrowBossStandingDeath.h"
#include "CCrowBossScript.h"

void CCrowBossStandingDeath::tick()
{
	GetOwner()->Animator3D()->Play(13, true);
}

void CCrowBossStandingDeath::Enter()
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
