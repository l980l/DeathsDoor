#include "pch.h"
#include "CKnightRunAttack.h"

void CKnightRunAttack::tick()
{
}

void CKnightRunAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(2, false);
}

void CKnightRunAttack::Exit()
{
}

void CKnightRunAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightRunAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightRunAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightRunAttack::CKnightRunAttack()
{
}

CKnightRunAttack::~CKnightRunAttack()
{
}
