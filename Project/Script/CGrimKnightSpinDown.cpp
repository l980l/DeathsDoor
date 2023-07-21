#include "pch.h"
#include "CGrimKnightSpinDown.h"

void CGrimKnightSpinDown::tick()
{
}

void CGrimKnightSpinDown::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(1, false);
}

void CGrimKnightSpinDown::Exit()
{
}

void CGrimKnightSpinDown::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightSpinDown::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightSpinDown::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightSpinDown::CGrimKnightSpinDown()
{
}

CGrimKnightSpinDown::~CGrimKnightSpinDown()
{
}
