#include "pch.h"
#include "CGrimKnightRightSpin.h"

void CGrimKnightRightSpin::tick()
{
}

void CGrimKnightRightSpin::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(5, false);
}

void CGrimKnightRightSpin::Exit()
{
}

void CGrimKnightRightSpin::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightRightSpin::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightRightSpin::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightRightSpin::CGrimKnightRightSpin()
{
}

CGrimKnightRightSpin::~CGrimKnightRightSpin()
{
}