#include "pch.h"
#include "CKnightChopAttackEnd.h"

void CKnightChopAttackEnd::tick()
{
}

void CKnightChopAttackEnd::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(9, false);
}

void CKnightChopAttackEnd::Exit()
{
}

void CKnightChopAttackEnd::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackEnd::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackEnd::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttackEnd::CKnightChopAttackEnd()
{
}

CKnightChopAttackEnd::~CKnightChopAttackEnd()
{
}
