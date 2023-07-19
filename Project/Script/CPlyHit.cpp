#include "pch.h"
#include "CPlyHit.h"
#include "CPlayerScript.h"

CPlyHit::CPlyHit()
{
}

CPlyHit::~CPlyHit()
{
}

void CPlyHit::Enter()
{
	// Hit Anim 재생 끝나면 바로 Idle로 돌아가야 하므로 반복재생 false;
	GetOwner()->Animator3D()->Play(22, false);
	// 이미 Hit이므로 무적 활성화
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyHit::tick()
{
	if(GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::HIT)
	{ }
}

void CPlyHit::Exit()
{
	// 무적 비활성화
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}

void CPlyHit::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyHit::OnOverlap(CCollider2D* _Other)
{
}

void CPlyHit::EndOverlap(CCollider2D* _Other)
{
}
