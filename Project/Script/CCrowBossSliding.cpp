#include "pch.h"
#include "CCrowBossSliding.h"
#include "CCrowBossScript.h"

void CCrowBossSliding::tick()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CCrowBossSliding::Enter()
{
}

void CCrowBossSliding::Exit()
{
}

CCrowBossSliding::CCrowBossSliding()
{
}

CCrowBossSliding::~CCrowBossSliding()
{
}
