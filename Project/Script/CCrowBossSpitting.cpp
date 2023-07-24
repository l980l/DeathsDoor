#include "pch.h"
#include "CCrowBossSpitting.h"
#include "CCrowBossScript.h"

void CCrowBossSpitting::tick()
{
	GetOwner()->Animator3D()->Play(2, false);
}

void CCrowBossSpitting::Enter()
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
