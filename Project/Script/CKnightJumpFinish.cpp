#include "pch.h"
#include "CKnightJumpFinish.h"

void CKnightJumpFinish::tick()
{
}

void CKnightJumpFinish::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(6, false);
}

void CKnightJumpFinish::Exit()
{
}

void CKnightJumpFinish::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpFinish::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpFinish::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpFinish::CKnightJumpFinish()
{
}

CKnightJumpFinish::~CKnightJumpFinish()
{
}
