#include "pch.h"
#include "CKnightChopAttack.h"
#include "CSoundScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CGameCameraScript.h"
#include <Engine/CRenderMgr.h>

void CKnightChopAttack::tick()
{
	m_fTime += DT;
	float fRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();
	if (!m_bCameraShake && fRatio >= 0.8f)
	{
		CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);
		m_bCameraShake = true;
	}
}

void CKnightChopAttack::Enter()
{
	
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(8, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Knight\\KnightSlam1.ogg", 1, 0.1);

}

void CKnightChopAttack::Exit()
{
}

void CKnightChopAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttack::CKnightChopAttack()
{
}

CKnightChopAttack::~CKnightChopAttack()
{
}
