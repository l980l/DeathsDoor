#include "pch.h"
#include "CKnightChopAttack.h"

void CKnightChopAttack::tick()
{
}

void CKnightChopAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(8, false);
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
