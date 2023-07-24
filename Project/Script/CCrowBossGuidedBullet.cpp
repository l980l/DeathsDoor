#include "pch.h"
#include "CCrowBossGuidedBullet.h"
#include "CCrowBossScript.h"

void CCrowBossGuidedBullet::Enter()
{
	GetOwner()->Animator3D()->Play(5, true);
}

void CCrowBossGuidedBullet::tick()
{
}

void CCrowBossGuidedBullet::Exit()
{
}

CCrowBossGuidedBullet::CCrowBossGuidedBullet()
{
}

CCrowBossGuidedBullet::~CCrowBossGuidedBullet()
{
}
