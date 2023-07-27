#include "pch.h"
#include "CCrowBossWalk.h"
#include "CCrowBossScript.h"

void CCrowBossWalk::Enter()
{
	GetOwner()->Animator3D()->Play(11, true);
}

void CCrowBossWalk::tick()
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
