#include "pch.h"
#include "CGrimKnightGuardStay.h"

void CGrimKnightGuardStay::tick()
{
}

void CGrimKnightGuardStay::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(12, true);
}

void CGrimKnightGuardStay::Exit()
{
}

void CGrimKnightGuardStay::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuardStay::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuardStay::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightGuardStay::CGrimKnightGuardStay()
{
}

CGrimKnightGuardStay::~CGrimKnightGuardStay()
{
}
