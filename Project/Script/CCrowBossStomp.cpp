#include "pch.h"
#include "CCrowBossStomp.h"
#include "CCrowBossScript.h"

void CCrowBossStomp::tick()
{
	GetOwner()->Animator3D()->Play(10, true);
}

void CCrowBossStomp::Enter()
{
}

void CCrowBossStomp::Exit()
{
}

CCrowBossStomp::CCrowBossStomp()
{
}

CCrowBossStomp::~CCrowBossStomp()
{
}
