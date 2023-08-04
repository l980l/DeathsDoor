#include "pch.h"
#include "CKnightWalk.h"

void CKnightWalk::tick()
{
}

void CKnightWalk::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(1, true);
}

void CKnightWalk::Exit()
{
}

void CKnightWalk::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightWalk::OnOverlap(CCollider2D* _Other)
{
}

void CKnightWalk::EndOverlap(CCollider2D* _Other)
{
}

CKnightWalk::CKnightWalk()
{
}

CKnightWalk::~CKnightWalk()
{
}
