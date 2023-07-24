#include "pch.h"
#include "CGrimKnightMelee.h"
#include "CLevelSaveLoadInScript.h"

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
	
	//공격 prefab 생성
	//CLevelSaveLoadInScript script;
	//script.SpawnPrefab(L"Melee", 5, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CGrimKnightMelee::Exit()
{
}

void CGrimKnightMelee::BeginOverlap(CCollider2D* _Other)
{
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
