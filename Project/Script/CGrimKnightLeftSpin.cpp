#include "pch.h"
#include "CGrimKnightLeftSpin.h"

void CGrimKnightLeftSpin::tick()
{
}

void CGrimKnightLeftSpin::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(4, false);
}

void CGrimKnightLeftSpin::Exit()
{
}

void CGrimKnightLeftSpin::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLeftSpin::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLeftSpin::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightLeftSpin::CGrimKnightLeftSpin()
{
}

CGrimKnightLeftSpin::~CGrimKnightLeftSpin()
{
}
