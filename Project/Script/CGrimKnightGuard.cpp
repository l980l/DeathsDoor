#include "pch.h"
#include "CGrimKnightGuard.h"

void CGrimKnightGuard::tick()
{
}

void CGrimKnightGuard::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(11, false);
}

void CGrimKnightGuard::Exit()
{
}

void CGrimKnightGuard::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuard::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuard::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightGuard::CGrimKnightGuard()
{
}

CGrimKnightGuard::~CGrimKnightGuard()
{
}
