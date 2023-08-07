#include "pch.h"
#include "CKnightRunAttack.h"
#include "CLevelSaveLoadInScript.h"

void CKnightRunAttack::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"JumpReady");
	}
}

void CKnightRunAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(2, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CKnightRunAttack::Exit()
{
}

void CKnightRunAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightRunAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightRunAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightRunAttack::CKnightRunAttack()
{
}

CKnightRunAttack::~CKnightRunAttack()
{
}
