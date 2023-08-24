#include "pch.h"
#include "CGrimKnightIdle.h"

CGrimKnightIdle::CGrimKnightIdle()
{
}

CGrimKnightIdle::~CGrimKnightIdle()
{
}

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
