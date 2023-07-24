#include "pch.h"
#include "CCrowBossDeath.h"
#include "CCrowBossScript.h"

void CCrowBossDeath::tick()
{
	GetOwner()->Animator3D()->Play(7, true);
}

void CCrowBossDeath::Enter()
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
