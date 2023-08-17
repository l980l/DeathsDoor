#include "pch.h"
#include "CPlyDance.h"
#include "CPlayerScript.h"
#include <Engine/CRenderMgr.h>
#include "CGameCameraScript.h"

CPlyDance::CPlyDance()
	: m_fCameraZoomIn(0.f)
{
}

CPlyDance::~CPlyDance()
{
}

void CPlyDance::Enter()
{
	// �¸����� �� ���� ��? ���Ƽ� ���� ��ȯ
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::DANCE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDance::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");

	m_fCameraZoomIn += DT;

	if (m_fCameraZoomIn <= 5.f)
	{
		CRenderMgr::GetInst()->GetMainCam()->SetScale(0.6f + 0.6f * (m_fCameraZoomIn / 5.f));
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->SetCutSceneView(true);
	}
}

void CPlyDance::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}
