#include "pch.h"
#include "CCrowBossCutScene.h"
#include "CCrowBossScript.h"

void CCrowBossCutScene::tick()
{
	GetOwner()->Animator3D()->Play(1, false);
}

void CCrowBossCutScene::Enter()
{
}

void CCrowBossCutScene::Exit()
{
}

CCrowBossCutScene::CCrowBossCutScene()
{
}

CCrowBossCutScene::~CCrowBossCutScene()
{
}
