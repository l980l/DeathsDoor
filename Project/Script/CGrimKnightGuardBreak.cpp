#include "pch.h"
#include "CGrimKnightGuardBreak.h"

void CGrimKnightGuardBreak::tick()
{
}

void CGrimKnightGuardBreak::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(3, false);
}

void CGrimKnightGuardBreak::Exit()
{
}

void CGrimKnightGuardBreak::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuardBreak::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuardBreak::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightGuardBreak::CGrimKnightGuardBreak()
{
}

CGrimKnightGuardBreak::~CGrimKnightGuardBreak()
{
}
