#include "pch.h"
#include "CKnightSpinAttack.h"
#include "CLevelSaveLoadInScript.h"

CKnightSpinAttack::CKnightSpinAttack()
{
}

CKnightSpinAttack::~CKnightSpinAttack()
{
}

void CKnightSpinAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(12, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\SpinAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CKnightSpinAttack::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Trace");
	}

	
}

void CKnightSpinAttack::Exit()
{
}
