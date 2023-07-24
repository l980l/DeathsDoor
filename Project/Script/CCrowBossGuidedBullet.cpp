#include "pch.h"
#include "CCrowBossGuidedBullet.h"
#include "CCrowBossScript.h"

void CCrowBossGuidedBullet::tick()
{
	GetOwner()->Animator3D()->Play(5, true);
}

void CCrowBossGuidedBullet::Enter()
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
