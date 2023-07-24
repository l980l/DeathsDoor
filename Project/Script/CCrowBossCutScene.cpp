#include "pch.h"
#include "CCrowBossCutScene.h"
#include "CCrowBossScript.h"

void CCrowBossCutScene::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);
}

void CCrowBossCutScene::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"RightSpin");
	}
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
