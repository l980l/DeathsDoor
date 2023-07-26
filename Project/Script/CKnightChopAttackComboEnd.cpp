#include "pch.h"
#include "CKnightChopAttackComboEnd.h"

void CKnightChopAttackComboEnd::tick()
{
}

void CKnightChopAttackComboEnd::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(11, false);
}

void CKnightChopAttackComboEnd::Exit()
{
}

void CKnightChopAttackComboEnd::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackComboEnd::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackComboEnd::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttackComboEnd::CKnightChopAttackComboEnd()
{
}

CKnightChopAttackComboEnd::~CKnightChopAttackComboEnd()
{
}
