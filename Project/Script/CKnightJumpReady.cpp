#include "pch.h"
#include "CKnightJumpReady.h"

void CKnightJumpReady::tick()
{
}

void CKnightJumpReady::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(5, false);
}

void CKnightJumpReady::Exit()
{
}

void CKnightJumpReady::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpReady::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpReady::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpReady::CKnightJumpReady()
{
}

CKnightJumpReady::~CKnightJumpReady()
{
}
