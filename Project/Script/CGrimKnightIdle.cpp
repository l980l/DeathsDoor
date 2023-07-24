#include "pch.h"
#include "CGrimKnightIdle.h"

void CGrimKnightIdle::tick()
{
}

void CGrimKnightIdle::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(0, true);
}

void CGrimKnightIdle::Exit()
{
}

void CGrimKnightIdle::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightIdle::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightIdle::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightIdle::CGrimKnightIdle()
{
}

CGrimKnightIdle::~CGrimKnightIdle()
{
}
