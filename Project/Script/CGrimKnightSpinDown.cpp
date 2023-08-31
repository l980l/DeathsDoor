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

void CGrimKnightSpinDown::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);
}

void CGrimKnightSpinDown::tick()
{	
	if (GetOwner()->Animator3D()->IsFinish())
	{
		CSoundScript* pSoundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = pSoundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceTwirlSlam.ogg", 1, 0.1f);
		ChangeState(L"SpinUp");
	}
}

void CGrimKnightSpinDown::Exit()
{
	CLevelSaveLoadInScript::SpawnPrefab(L"prefab\\JumpAttack.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 0.2f);
	
}
