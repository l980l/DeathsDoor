#include "pch.h"
#include "CCrowBossCutScene.h"
#include "CCrowBossScript.h"
#include "CGameCameraScript.h"

#include <Engine/CRenderMgr.h>

void CCrowBossCutScene::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);

	// Target�� Owner�� �ٲٰ�, MainCam�� CutScene ���� ����.
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetTarget(GetOwner());
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetCutSceneView(true);
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
	// Target�� �ٽ� Player�� �����ϰ�, MainCam�� �Ϲ� ���� ����.
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetTargetPlayer();
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetCutSceneView(false);
}

CCrowBossCutScene::CCrowBossCutScene()
{
}

CCrowBossCutScene::~CCrowBossCutScene()
{
}
