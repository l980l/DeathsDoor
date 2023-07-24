#include "pch.h"
#include "CCrowBossJump.h"
#include "CCrowBossScript.h"

void CCrowBossJump::tick()
{
	GetOwner()->Animator3D()->Play(9, true);
}

void CCrowBossJump::Enter()
{
}

void CCrowBossJump::Exit()
{
}

CCrowBossJump::CCrowBossJump()
{
}

CCrowBossJump::~CCrowBossJump()
{
}
