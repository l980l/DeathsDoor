#include "pch.h"
#include "CCrowBossBatBullet.h"
#include "CCrowBossScript.h"

void CCrowBossBatBullet::tick()
{
	GetOwner()->Animator3D()->Play(6, true);
}

void CCrowBossBatBullet::Enter()
{
}

void CCrowBossBatBullet::Exit()
{
}

CCrowBossBatBullet::CCrowBossBatBullet()
{
}

CCrowBossBatBullet::~CCrowBossBatBullet()
{
}
