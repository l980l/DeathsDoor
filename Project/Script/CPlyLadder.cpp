#include "pch.h"
#include "CPlyLadder.h"
#include "CPlayerScript.h"

CPlyLadder::CPlyLadder()
{
}

CPlyLadder::~CPlyLadder()
{
}

void CPlyLadder::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_UP, true);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyLadder::tick()
{
	if (KEY_RELEASE(KEY::UP))
	{
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_UP, false);
	}
}

void CPlyLadder::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}

void CPlyLadder::Move()
{
	if (KEY_PRESSED(KEY::UP))
	{
		GetOwner()->Rigidbody()->AddVelocity(Vec3(0.f, m_fSpeed, 0.f));
	}
	if (KEY_PRESSED(KEY::DOWN))
	{
		GetOwner()->Rigidbody()->AddVelocity(Vec3(0.f, -m_fSpeed, 0.f));
	}

}

void CPlyLadder::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyLadder::OnOverlap(CCollider2D* _Other)
{
}

void CPlyLadder::EndOverlap(CCollider2D* _Other)
{
}
