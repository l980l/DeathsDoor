#include "pch.h"
#include "CGrimKnightSpinUp.h"

void CGrimKnightSpinUp::tick()
{
}

void CGrimKnightSpinUp::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(2, false);
}

void CGrimKnightSpinUp::Exit()
{
}

void CGrimKnightSpinUp::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightSpinUp::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightSpinUp::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightSpinUp::CGrimKnightSpinUp()
{
}

CGrimKnightSpinUp::~CGrimKnightSpinUp()
{
}
