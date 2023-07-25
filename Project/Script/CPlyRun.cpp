#include "pch.h"
#include "CPlyRun.h"
#include "CPlayerScript.h"

CPlyRun::CPlyRun()
	: m_fSpeed(0.f)
	, m_fTimeToIdle(0.f)
	, m_bIce(false)
{
}

CPlyRun::~CPlyRun()
{
}

void CPlyRun::Enter()
{
	m_fSpeed = GetOwnerScript()->GetStat().Speed;
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::RUN, true);
	GetOwner()->Rigidbody()->SetVelocityLimit(m_fSpeed);
}

void CPlyRun::tick()
{
	Move();

	// ������ �ִٸ�(���� �����Ӱ� ��ġ ���̰� ���ٸ�) Idle ��ȯ�ð� +
	if (Vec3(0.f, 0.f, 0.f) == GetOwner()->Transform()->GetWorldPos() - GetOwner()->Transform()->GetPrevPos())
	{
		m_fTimeToIdle += DT;
	}
	else
	{
		CalcDir();
		m_fTimeToIdle = 0.f;
	}

	if (KEY_TAP(KEY::LBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Attack");
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeMagicState();
	}
	// Idle ��ȯ�ð��� 0.1�� �Ѿ��ٸ� Idle��
	else if (m_fTimeToIdle >= 0.02f)
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Walk");
	}
	else if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}
}

void CPlyRun::Exit()
{
	m_fTimeToIdle = 0.f;
}

void CPlyRun::Move()
{
	Vec3 Velocity = {};
	if (KEY_PRESSED(KEY::W))
	{
		Velocity.z = m_fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		Velocity.z = -m_fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		Velocity.x = -m_fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		Velocity.x = m_fSpeed;
	}

	GetOwner()->Rigidbody()->SetVelocity(Velocity);
}

void CPlyRun::CalcDir()
{
	Vec3 vPrevPos = GetOwner()->Transform()->GetPrevPos();
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();

	float Dir = GetDir(vPrevPos, vCurPos, false);

	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, Dir, 0.f);
}

void CPlyRun::BeginOverlap(CCollider2D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER)
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}
