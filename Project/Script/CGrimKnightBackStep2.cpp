#include "pch.h"
#include "CGrimKnightBackStep2.h"

void CGrimKnightBackStep2::tick()
{
}

void CGrimKnightBackStep2::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(10, false);
}

void CGrimKnightBackStep2::Exit()
{
}

void CGrimKnightBackStep2::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightBackStep2::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightBackStep2::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightBackStep2::CGrimKnightBackStep2()
{
}

CGrimKnightBackStep2::~CGrimKnightBackStep2()
{
}
