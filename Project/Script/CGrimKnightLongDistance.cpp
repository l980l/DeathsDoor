#include "pch.h"
#include "CGrimKnightLongDistance.h"
#include "CLevelSaveLoadInScript.h"

void CGrimKnightLongDistance::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Trace");
	}
}

void CGrimKnightLongDistance::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(7, false);
	
	//Ghost prefab »ý¼º
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\Ghost.prefab", 5, GetOwner()->Transform()->GetWorldPos(), 5.f);
}

void CGrimKnightLongDistance::Exit()
{
}

void CGrimKnightLongDistance::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLongDistance::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLongDistance::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightLongDistance::CGrimKnightLongDistance()
{
}

CGrimKnightLongDistance::~CGrimKnightLongDistance()
{
}
