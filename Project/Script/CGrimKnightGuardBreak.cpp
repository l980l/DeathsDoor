#include "pch.h"
#include "CGrimKnightGuardBreak.h"
#include "CSoundScript.h"

CGrimKnightGuardBreak::CGrimKnightGuardBreak()
{
}

CGrimKnightGuardBreak::~CGrimKnightGuardBreak()
{
}

void CGrimKnightGuardBreak::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"BackStep1");
	}
}

void CGrimKnightGuardBreak::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(3, false);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceShieldBreak.ogg", 1, 0.1);
}

void CGrimKnightGuardBreak::Exit()
{
}
