#include "pch.h"
#include "CKnightChopAttackCombo.h"
#include "CSoundScript.h"

void CKnightChopAttackCombo::tick()
{
	m_fTime += DT;
	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();
	if (!m_bCameraShake && fRatio >= 0.8f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);
		m_bCameraShake = true;
	}
}

void CKnightChopAttackCombo::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(10, false);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Knight\\KnightSlam2.ogg", 3, 0.1);
}

void CKnightChopAttackCombo::Exit()
{
}

void CKnightChopAttackCombo::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackCombo::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackCombo::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttackCombo::CKnightChopAttackCombo()
{
}

CKnightChopAttackCombo::~CKnightChopAttackCombo()
{
}
