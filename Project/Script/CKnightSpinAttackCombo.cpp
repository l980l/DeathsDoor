#include "pch.h"
#include "CKnightSpinAttackCombo.h"

void CKnightSpinAttackCombo::tick()
{
}

void CKnightSpinAttackCombo::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(13, false);
}

void CKnightSpinAttackCombo::Exit()
{
}

void CKnightSpinAttackCombo::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightSpinAttackCombo::OnOverlap(CCollider2D* _Other)
{
}

void CKnightSpinAttackCombo::EndOverlap(CCollider2D* _Other)
{
}

CKnightSpinAttackCombo::CKnightSpinAttackCombo()
{
}

CKnightSpinAttackCombo::~CKnightSpinAttackCombo()
{
}
