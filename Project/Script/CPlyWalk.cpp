#include "pch.h"
#include "CPlyWalk.h"

CPlyWalk::CPlyWalk()
	: m_fSpeed(500.f)
	, m_fTimeToIdle()
{
}

CPlyWalk::~CPlyWalk()
{
}

void CPlyWalk::tick()
{
	Move();

	// 가만히 있다면(이전 프레임과 위치 차이가 없다면) Idle 전환시간 +
	if (Vec3(0.f, 0.f, 0.f) == GetOwner()->Transform()->GetWorldPos() - GetOwner()->Transform()->GetPrevPos())
		m_fTimeToIdle += DT;
	else
		m_fTimeToIdle = 0.f;

	// Idle 전환시간이 0.1을 넘었다면 Idle로
	if (m_fTimeToIdle >= 0.1f)
		ChangeState(L"Idle");
}

void CPlyWalk::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::WALK, true);
}

void CPlyWalk::Exit()
{
}

void CPlyWalk::Move()
{
	Vec3 Velocity = {};
	if (KEY_PRESSED(KEY::W))
	{
		//GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, m_fSpeed));
		Velocity.z = m_fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		//GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, -m_fSpeed));
		Velocity.z = -m_fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		//GetOwner()->Rigidbody()->SetVelocity(Vec3(-m_fSpeed, 0.f, 0.f));
		Velocity.x = -m_fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		//GetOwner()->Rigidbody()->SetVelocity(Vec3(m_fSpeed , 0.f, 0.f));
		Velocity.x = m_fSpeed;
	}

	GetOwner()->Rigidbody()->SetVelocity(Velocity);
}

void CPlyWalk::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyWalk::OnOverlap(CCollider2D* _Other)
{
}

void CPlyWalk::EndOverlap(CCollider2D* _Other)
{
}
