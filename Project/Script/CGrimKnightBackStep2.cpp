#include "pch.h"
#include "CGrimKnightBackStep2.h"

CGrimKnightBackStep2::CGrimKnightBackStep2()
{
}

CGrimKnightBackStep2::~CGrimKnightBackStep2()
{
}

void CGrimKnightBackStep2::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(10, false);
}

void CGrimKnightBackStep2::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"LongDistance");
	}
}

void CGrimKnightBackStep2::Exit()
{
}
