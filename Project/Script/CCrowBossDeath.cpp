#include "pch.h"
#include "CCrowBossDeath.h"
#include "CCrowBossScript.h"

void CCrowBossDeath::Enter()
{
	GetOwner()->Animator3D()->Play(7, true);
}

void CCrowBossDeath::tick()
{
}

void CCrowBossDeath::Exit()
{
}

CCrowBossDeath::CCrowBossDeath()
{
}

CCrowBossDeath::~CCrowBossDeath()
{
}
