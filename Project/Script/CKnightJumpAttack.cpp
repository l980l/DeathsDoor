#include "pch.h"
#include "CKnightJumpAttack.h"

void CKnightJumpAttack::tick()
{
}

void CKnightJumpAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(7, false);
}

void CKnightJumpAttack::Exit()
{
}

void CKnightJumpAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpAttack::CKnightJumpAttack()
{
}

CKnightJumpAttack::~CKnightJumpAttack()
{
}
