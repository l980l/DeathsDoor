#include "pch.h"
#include "CGrimKnightMelee.h"

void CGrimKnightMelee::tick()
{
}

void CGrimKnightMelee::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(8, false);
}

void CGrimKnightMelee::Exit()
{
}

void CGrimKnightMelee::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightMelee::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightMelee::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightMelee::CGrimKnightMelee()
{
}

CGrimKnightMelee::~CGrimKnightMelee()
{
}
