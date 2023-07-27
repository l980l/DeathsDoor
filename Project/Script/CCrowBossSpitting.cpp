#include "pch.h"
#include "CCrowBossSpitting.h"
#include "CCrowBossScript.h"

void CCrowBossSpitting::Enter()
{
	GetOwner()->Animator3D()->Play(2, false);
}

void CCrowBossSpitting::tick()
{
}

void CCrowBossSpitting::Exit()
{
}

CCrowBossSpitting::CCrowBossSpitting()
{
}

CCrowBossSpitting::~CCrowBossSpitting()
{
}
