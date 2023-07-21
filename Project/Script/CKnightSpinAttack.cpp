#include "pch.h"
#include "CKnightSpinAttack.h"

void CKnightSpinAttack::tick()
{
}

void CKnightSpinAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(12, false);
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
