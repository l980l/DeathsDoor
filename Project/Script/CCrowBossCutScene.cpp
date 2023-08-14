#include "pch.h"
#include "CCrowBossCutScene.h"
#include "CCrowBossScript.h"
#include "CGameCameraScript.h"

#include <Engine/CRenderMgr.h>

void CCrowBossCutScene::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);

	// Target을 Owner로 바꾸고, MainCam을 CutScene 모드로 변경.
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetTarget(GetOwner());
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetCutSceneView(true);
	
	m_fTime = 0.f;
	m_bCameraShake = false;
}

void CCrowBossCutScene::tick()
{
	// Camera Shake
	m_fTime += DT;

	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();

	if (!m_bCameraShake && fRatio >= 0.5f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.5f);
		m_bCameraShake = true;
	}


	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"RightSpin");
	}
}

void CCrowBossCutScene::Exit()
{
	// Target을 다시 Player로 변경하고, MainCam을 일반 모드로 변경.
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetTargetPlayer();
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetCutSceneView(false);
}

CCrowBossCutScene::CCrowBossCutScene() :
	m_fTime(0.f),
	m_bCameraShake(false)
{
}

CCrowBossCutScene::~CCrowBossCutScene()
{
}
