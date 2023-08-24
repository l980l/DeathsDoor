#include "pch.h"
#include "CKnightRunAttack.h"
#include "CLevelSaveLoadInScript.h"

CKnightRunAttack::CKnightRunAttack()
{
}

CKnightRunAttack::~CKnightRunAttack()
{
}

void CKnightRunAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(2, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CKnightRunAttack::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"JumpReady");
	}
}

void CKnightRunAttack::Exit()
{
}
