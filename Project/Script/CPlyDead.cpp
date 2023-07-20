#include "pch.h"
#include "CPlyDead.h"
#include "CPlayerScript.h"

CPlyDead::CPlyDead()
{
}

CPlyDead::~CPlyDead()
{
}

void CPlyDead::tick()
{
}

void CPlyDead::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HIT_IDLE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDead::Exit()
{
}

void CPlyDead::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyDead::OnOverlap(CCollider2D* _Other)
{
}

void CPlyDead::EndOverlap(CCollider2D* _Other)
{
}