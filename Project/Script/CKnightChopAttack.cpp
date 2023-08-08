#include "pch.h"
#include "CKnightChopAttack.h"
#include "CLevelSaveLoadInScript.h"

void CKnightChopAttack::tick()
{
}

void CKnightChopAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(8, false);
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"prefab\\JumpAttack.prefab", 6, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CKnightChopAttack::Exit()
{
}

void CKnightChopAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttack::CKnightChopAttack()
{
}

CKnightChopAttack::~CKnightChopAttack()
{
}
