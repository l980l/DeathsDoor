#include "pch.h"
#include "CPlyLadder.h"
#include "CPlayerScript.h"

CPlyLadder::CPlyLadder()
	: m_fSpeed(300.f)
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
	Move();

	if (!(KEY_RELEASE(KEY::W)) || !(KEY_RELEASE(KEY::S)))
	{
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}

}

void CPlyLadder::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}

void CPlyLadder::Move()
{
	if (KEY_PRESSED(KEY::W))
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, m_fSpeed * DT, 0.f));
	}
	else if (KEY_PRESSED(KEY::S))
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, -m_fSpeed * DT, 0.f));
	}
}

void CPlyLadder::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER)
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	}
}

void CPlyLadder::OnOverlap(CCollider3D* _Other)
{
}

void CPlyLadder::EndOverlap(CCollider3D* _Other)
{
}
