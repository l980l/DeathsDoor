#include "pch.h"
#include "CKnightSpinAttack.h"
#include "CLevelSaveLoadInScript.h"

void CKnightSpinAttack::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Trace");
	}

	
}

void CKnightSpinAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(12, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\SpinAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CKnightSpinAttack::Exit()
{
}

void CKnightSpinAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightSpinAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightSpinAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightSpinAttack::CKnightSpinAttack()
{
}

CKnightSpinAttack::~CKnightSpinAttack()
{
}
