#include "pch.h"
#include "CKnightCutScene.h"

void CKnightCutScene::tick()
{
	m_fTime += DT;
	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();
	if (!m_bCameraShake && fRatio >= 0.8f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);
		m_bCameraShake = true;
	}
}

void CKnightCutScene::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(4, false);
}

void CKnightCutScene::Exit()
{
}

void CKnightCutScene::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightCutScene::OnOverlap(CCollider2D* _Other)
{
}

void CKnightCutScene::EndOverlap(CCollider2D* _Other)
{
}

CKnightCutScene::CKnightCutScene()
{
}

CKnightCutScene::~CKnightCutScene()
{
}
