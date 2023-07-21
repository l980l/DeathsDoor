#include "pch.h"
#include "CGrimKnightBackStep.h"

void CGrimKnightBackStep::tick()
{
}

void CGrimKnightBackStep::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(9, false);
}

void CGrimKnightBackStep::Exit()
{
}

void CGrimKnightBackStep::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightBackStep::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightBackStep::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightBackStep::CGrimKnightBackStep()
{
}

CGrimKnightBackStep::~CGrimKnightBackStep()
{
}
