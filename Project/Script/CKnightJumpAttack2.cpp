#include "pch.h"
#include "CKnightJumpAttack2.h"
#include "CLevelSaveLoadInScript.h"
#include "CSoundScript.h"

void CKnightJumpAttack2::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"JumpFinish");
	}

}

void CKnightJumpAttack2::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(14, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Knight\\KnightSlam1.ogg", 1, 0.1);
}

void CKnightJumpAttack2::Exit()
{
}

void CKnightJumpAttack2::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack2::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack2::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpAttack2::CKnightJumpAttack2()
{
}

CKnightJumpAttack2::~CKnightJumpAttack2()
{
}
