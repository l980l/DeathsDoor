#include "pch.h"
#include "CGrimKnightMelee.h"
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"
#include "CSoundScript.h"

void CGrimKnightMelee::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"SpinDown");
	}
}

void CGrimKnightMelee::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(8, false);
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceBite.ogg", 1, 0.1);
}

void CGrimKnightMelee::Exit()
{
	//공격 prefab 생성
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CGrimKnightMelee::BeginOverlap(CCollider2D* _Other)
{
	/*if (_Other->GetOwner()->GetName() == L"Player")
	{
		Stat playerStat= _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		playerStat.HP -= 1;
		
		_Other->GetOwner()->GetScript<CStateScript>()->SetStat(playerStat);
	}*/
}

void CGrimKnightMelee::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightMelee::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightMelee::CGrimKnightMelee()
{
}

CGrimKnightMelee::~CGrimKnightMelee()
{
}
