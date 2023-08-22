#include "pch.h"
#include "CKnightIdle.h"

CKnightIdle::CKnightIdle()
{
}

CKnightIdle::~CKnightIdle()
{
}

void CKnightIdle::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(0, false);
}

void CKnightIdle::tick()
{
}

void CKnightIdle::Exit()
{
}
