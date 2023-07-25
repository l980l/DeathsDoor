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
	Vec3 Velocity = Vec3(0.f, 0.f, 0.f);

	if (KEY_PRESSED(KEY::W))
	{
		Velocity.z += m_fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		Velocity.z -= m_fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		Velocity.x -= m_fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		Velocity.x += m_fSpeed;
	}

	GetOwner()->Rigidbody()->SetVelocity(Velocity);
}
void CPlyRun::CalcDir()
{
	Vec3 vPrevPos = GetOwner()->Transform()->GetPrevPos();
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 vPrevDir = GetOwner()->Transform()->GetRelativeRot();
	float PrevDir = vPrevDir.y;
	float Rot = GetDir(vPrevPos, vCurPos);
	GetOwner()->GetScript<CPlayerScript>()->SetDir(Rot);
	float Diff = Rot - PrevDir;

	if (Diff > XM_PI)
	{
		Diff = -(XM_2PI - Rot + PrevDir) * (180.f / XM_PI);
	}
	else if (Diff < -XM_PI)
	{
		Diff = (XM_2PI - PrevDir + Rot) * (180.f / XM_PI);
	}
	else
		Diff = (Rot - PrevDir) * (180.f / XM_PI);

	if (abs(Diff) > 0.1f)
	{
		bool bnegative = false;
		if (Diff < 0)
			bnegative = true;

		Diff = bnegative ? -2.3f / 180.f * XM_PI : 2.3f / 180.f * XM_PI;
	}
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, PrevDir + Diff, 0.f);
}

void CPlyRun::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER)
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}
