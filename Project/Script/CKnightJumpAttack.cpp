#include "pch.h"
#include "CKnightJumpAttack.h"
#include "CSoundScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CGameObject.h>

void CKnightJumpAttack::tick()
{
	m_fTime += DT;
	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();
	if (!m_bCameraShake && fRatio >= 0.8f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);
		m_bCameraShake = true;
	}
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"JumpAttack2");
	}
}

void CKnightJumpAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(7, false);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Knight\\KnightSlam1.ogg", 1, 0.1);
	
}

void CKnightJumpAttack::Exit()
{
}

void CKnightJumpAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpAttack::CKnightJumpAttack()
{
}

CKnightJumpAttack::~CKnightJumpAttack()
{
}
