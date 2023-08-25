#include "pch.h"
#include "CGrimKnightGuard.h"
#include "CSoundScript.h"

CGrimKnightGuard::CGrimKnightGuard()
{
}

CGrimKnightGuard::~CGrimKnightGuard()
{
}

void CGrimKnightGuard::Enter()
{
	GetOwner()->Animator3D()->Play(11, false);
}

void CGrimKnightGuard::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{		
		ChangeState(L"GuardStay");
	}
}

void CGrimKnightGuard::Exit()
{
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceShieldSlam.ogg", 1, 0.1);
}
