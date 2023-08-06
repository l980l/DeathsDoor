#include "pch.h"
#include "CPlyLadder.h"
#include "CPlayerScript.h"

CPlyLadder::CPlyLadder()
	: m_fSpeed(300.f)
	, m_fStartYPos(0.f)
	, m_fYDistance(0.f)
{
}

CPlyLadder::~CPlyLadder()
{
}

void CPlyLadder::Enter()
{
	m_fStartYPos = GetOwner()->Transform()->GetWorldPos().y;
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_UP, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyLadder::tick()
{
	if (!(KEY_RELEASE(KEY::W)) || !(KEY_RELEASE(KEY::S)))
	{
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}
	if (GetOwner()->Transform()->GetWorldPos().y - m_fStartYPos >= m_fYDistance)
	{
		if (GetOwner()->Animator3D()->GetCurClip() != (int)PLAYERANIM_TYPE::LADDER_FINISH)
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_FINISH, false);
		else if (GetOwner()->Animator3D()->IsFinish())
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	}
	else
	{
		Move();
	}
}

void CPlyLadder::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
	GetOwner()->Rigidbody()->ClearForce();
}

void CPlyLadder::Move()
{

	if (KEY_PRESSED(KEY::W))
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, m_fSpeed * DT, 0.f));
		if (GetOwner()->Animator3D()->GetCurClip() != (int)PLAYERANIM_TYPE::LADDER_UP)
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_UP, false);
	}
	else if (KEY_PRESSED(KEY::S))
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, -m_fSpeed * DT, 0.f));
		if (GetOwner()->Animator3D()->GetCurClip() != (int)PLAYERANIM_TYPE::LADDER_DOWN)
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_DOWN, false);
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
