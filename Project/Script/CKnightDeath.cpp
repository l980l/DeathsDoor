#include "pch.h"
#include "CKnightDeath.h"

void CKnightDeath::tick()
{
}

void CKnightDeath::Enter()
{
	//anim + paper burn
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(3, false);
}

void CKnightDeath::Exit()
{
}

void CKnightDeath::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightDeath::OnOverlap(CCollider2D* _Other)
{
}

void CKnightDeath::EndOverlap(CCollider2D* _Other)
{
}

CKnightDeath::CKnightDeath()
{
}

CKnightDeath::~CKnightDeath()
{
}
