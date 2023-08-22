#include "pch.h"
#include "CKnightChopAttackEnd.h"

CKnightChopAttackEnd::CKnightChopAttackEnd()
{
}

CKnightChopAttackEnd::~CKnightChopAttackEnd()
{
}

void CKnightChopAttackEnd::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(9, false);
}

void CKnightChopAttackEnd::tick()
{
}

void CKnightChopAttackEnd::Exit()
{
}
