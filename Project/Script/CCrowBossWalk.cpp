#include "pch.h"
#include "CCrowBossWalk.h"
#include "CCrowBossScript.h"

void CCrowBossWalk::tick()
{
	GetOwner()->Animator3D()->Play(11, true);
}

void CCrowBossWalk::Enter()
{
}

void CCrowBossWalk::Exit()
{
}

CCrowBossWalk::CCrowBossWalk()
{
}

CCrowBossWalk::~CCrowBossWalk()
{
}
