#include "pch.h"
#include "CCrowBossSlidingReady.h"
#include "CCrowBossScript.h"

void CCrowBossSlidingReady::tick()
{
	GetOwner()->Animator3D()->Play(4, true);
}

void CCrowBossSlidingReady::Enter()
{
}

void CCrowBossSlidingReady::Exit()
{
}

CCrowBossSlidingReady::CCrowBossSlidingReady()
{
}

CCrowBossSlidingReady::~CCrowBossSlidingReady()
{
}
