#include "pch.h"
#include "CGrimKnightLongDistance.h"

void CGrimKnightLongDistance::tick()
{
}

void CGrimKnightLongDistance::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(7, false);
}

void CGrimKnightLongDistance::Exit()
{
}

void CGrimKnightLongDistance::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLongDistance::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLongDistance::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightLongDistance::CGrimKnightLongDistance()
{
}

CGrimKnightLongDistance::~CGrimKnightLongDistance()
{
}
