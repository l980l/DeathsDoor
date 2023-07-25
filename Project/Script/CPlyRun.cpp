#include "pch.h"
#include "CPlyRun.h"
#include "CPlayerScript.h"

CPlyRun::CPlyRun()
	: m_fSpeed(0.f)
	, m_fTimeToIdle(0.f)
	, m_fRotDelay(0.f)
	, m_fRot(0.f)
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

	//if(0.f != m_fRotDelay)


	// 가만히 있다면(이전 프레임과 위치 차이가 없다면) Idle 전환시간 +
	if (!(KEY_PRESSED(KEY::W)) && !(KEY_PRESSED(KEY::A)) && !(KEY_PRESSED(KEY::S)) && !(KEY_PRESSED(KEY::D)))
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
	// Idle 전환시간이 0.1을 넘었다면 Idle로
	else if (m_fTimeToIdle >= 0.02f)
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Walk");
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
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
	Vec3 vPrevPos =  GetOwner()->Transform()->GetPrevPos();
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 vPrevDir = GetOwner()->Transform()->GetRelativeRot();
	float PrevDir = vPrevDir.y;
	float Rot = GetDir(vPrevPos, vCurPos);
	float Diff = (Rot - PrevDir) * (180.f / XM_PI);

	if(Diff != 0.f)
	{
		if (abs(Diff) > 1)
		{
			bool bnegative = false;
			if (Diff < 0)
				bnegative = true;

			Diff = bnegative ? -1.f / 180.f * XM_PI : 1.f / 180.f * XM_PI;
		}
		else
			Diff = 0.f;
		GetOwner()->GetScript<CPlayerScript>()->SetDir(PrevDir + Diff);
		GetOwner()->GetScript<CPlayerScript>()->SetDiff(Diff);

	}
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, PrevDir + Diff, 0.f);
}

void CPlyRun::BeginOverlap(CCollider2D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER)
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}
