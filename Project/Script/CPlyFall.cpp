#include "pch.h"
#include "CPlyFall.h"

CPlyFall::CPlyFall()
{
}

CPlyFall::~CPlyFall()
{
}

void CPlyFall::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::FALL, true);
}

void CPlyFall::tick()
{
	if (GetOwner()->Rigidbody()->IsGround())
		ChangeState(L"Idle");
}

void CPlyFall::Exit()
{
}

void CPlyFall::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyFall::OnOverlap(CCollider2D* _Other)
{
}

void CPlyFall::EndOverlap(CCollider2D* _Other)
{
}
