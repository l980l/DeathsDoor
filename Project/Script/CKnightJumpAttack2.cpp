#include "pch.h"
#include "CKnightJumpAttack2.h"
#include "CLevelSaveLoadInScript.h"

void CKnightJumpAttack2::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"JumpFinish");
	}
	CLevelSaveLoadInScript script;
	script.SpawnPrefab(L"JumpAttack", 5, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CKnightJumpAttack2::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(14, false);
}

void CKnightJumpAttack2::Exit()
{
}

void CKnightJumpAttack2::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack2::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack2::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpAttack2::CKnightJumpAttack2()
{
}

CKnightJumpAttack2::~CKnightJumpAttack2()
{
}
