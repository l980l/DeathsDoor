#include "pch.h"
#include "CPlyDead.h"
#include "CPlayerScript.h"

CPlyDead::CPlyDead()
{
}

CPlyDead::~CPlyDead()
{
}

void CPlyDead::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HIT_IDLE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDead::tick()
{
	// 사망 글씨로 화면이 덮히면서 Hall Level에서 다시 입장
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