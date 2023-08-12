#include "pch.h"
#include "CGrimKnightGuard.h"
#include "CSoundScript.h"

void CGrimKnightGuard::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceShieldSlam.ogg", 1, 0.1);
		
		ChangeState(L"GuardStay");
	}
}

void CGrimKnightGuard::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(11, false);

}

void CGrimKnightGuard::Exit()
{
}

void CGrimKnightGuard::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuard::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuard::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightGuard::CGrimKnightGuard()
{
}

CGrimKnightGuard::~CGrimKnightGuard()
{
}
