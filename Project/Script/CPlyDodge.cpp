#include "pch.h"
#include "CPlyDodge.h"
#include "CPlayerScript.h"

CPlyDodge::CPlyDodge()
{
}

CPlyDodge::~CPlyDodge()
{
}

void CPlyDodge::Enter()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDodge::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
}

void CPlyDodge::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}

void CPlyDodge::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyDodge::OnOverlap(CCollider2D* _Other)
{
}

void CPlyDodge::EndOverlap(CCollider2D* _Other)
{
}
