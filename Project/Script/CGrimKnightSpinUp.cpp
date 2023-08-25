#include "pch.h"
#include "CGrimKnightSpinUp.h"

CGrimKnightSpinUp::CGrimKnightSpinUp()
{
}

CGrimKnightSpinUp::~CGrimKnightSpinUp()
{
}

void CGrimKnightSpinUp::Enter()
{
	GetOwner()->Animator3D()->Play(2, false);
}

void CGrimKnightSpinUp::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Guard");
	}
}

void CGrimKnightSpinUp::Exit()
{
}
