#include "pch.h"
#include "CKnightJumpFinish.h"
#include "CSoundScript.h"

void CKnightJumpFinish::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"SpinAttack");
	}
}

void CKnightJumpFinish::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(6, false);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Knight\\KnightJump4.ogg", 1, 0.1);
}

void CKnightJumpFinish::Exit()
{
}

void CKnightJumpFinish::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpFinish::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpFinish::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpFinish::CKnightJumpFinish()
{
}

CKnightJumpFinish::~CKnightJumpFinish()
{
}
