#include "pch.h"
#include "CGrimKnightChase.h"

void CGrimKnightChase::tick()
{
}

void CGrimKnightChase::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(6, true);
}

void CGrimKnightChase::Exit()
{
}

void CGrimKnightChase::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightChase::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightChase::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightChase::CGrimKnightChase()
{
}

CGrimKnightChase::~CGrimKnightChase()
{
}
