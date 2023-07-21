#include "pch.h"
#include "CKnightIdle.h"

void CKnightIdle::tick()
{
}

void CKnightIdle::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(0, false);
}

void CKnightIdle::Exit()
{
}

void CKnightIdle::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightIdle::OnOverlap(CCollider2D* _Other)
{
}

void CKnightIdle::EndOverlap(CCollider2D* _Other)
{
}

CKnightIdle::CKnightIdle()
{
}

CKnightIdle::~CKnightIdle()
{
}
