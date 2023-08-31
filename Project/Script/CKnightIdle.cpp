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
	GetOwner()->Animator3D()->Play(0, false);
}

void CKnightIdle::tick()
{
}

void CKnightIdle::Exit()
{
}

void CKnightIdle::BeginOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::PLAYER == _Other->GetOwner()->GetLayerIndex())
	{
		ChangeState(L"RunAttack");
	}
}
