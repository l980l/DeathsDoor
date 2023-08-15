#include "pch.h"
#include "CKnightChopAttackComboEnd.h"

void CKnightChopAttackComboEnd::tick()
{
	m_fTime += DT;
	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();
	if (!m_bCameraShake && fRatio >= 0.8f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);
		m_bCameraShake = true;
	}
}

void CKnightChopAttackComboEnd::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(11, false);
}

void CKnightChopAttackComboEnd::Exit()
{
}

void CKnightChopAttackComboEnd::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackComboEnd::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackComboEnd::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttackComboEnd::CKnightChopAttackComboEnd()
{
}

CKnightChopAttackComboEnd::~CKnightChopAttackComboEnd()
{
}
