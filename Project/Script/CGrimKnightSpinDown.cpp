#include "pch.h"
#include "CGrimKnightSpinDown.h"
#include "CLevelSaveLoadInScript.h"
#include "CSoundScript.h"

CGrimKnightSpinDown::CGrimKnightSpinDown()
{
}

CGrimKnightSpinDown::~CGrimKnightSpinDown()
{
}

void CGrimKnightSpinDown::tick()
{
	
	if (GetOwner()->Animator3D()->IsFinish())
	{
		CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceTwirlSlam.ogg", 1, 0.1);
		ChangeState(L"SpinUp");
	}
}

void CGrimKnightSpinDown::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(1, false);
	
	
}

void CGrimKnightSpinDown::Exit()
{
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 0.2f);
	
}
