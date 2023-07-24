#include "pch.h"
#include "CKnightChopAttackCombo.h"

void CKnightChopAttackCombo::tick()
{
}

void CKnightChopAttackCombo::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(10, false);
}

void CKnightChopAttackCombo::Exit()
{
}

void CKnightChopAttackCombo::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackCombo::OnOverlap(CCollider2D* _Other)
{
}

void CKnightChopAttackCombo::EndOverlap(CCollider2D* _Other)
{
}

CKnightChopAttackCombo::CKnightChopAttackCombo()
{
}

CKnightChopAttackCombo::~CKnightChopAttackCombo()
{
}
