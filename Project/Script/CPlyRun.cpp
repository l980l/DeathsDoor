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
}

void CPlyRun::tick()
{
	Move();

	// ������ �ִٸ�(���� �����Ӱ� ��ġ ���̰� ���ٸ�) Idle ��ȯ�ð� +
	if (!(KEY_PRESSED(KEY::W)) && !(KEY_PRESSED(KEY::A)) && !(KEY_PRESSED(KEY::S)) && !(KEY_PRESSED(KEY::D)))
	{
		m_fTimeToIdle += DT;
	}
	else
	{
		GetOwner()->Transform()->CalcDir();
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

	if (m_bIce)
		GetOwner()->Rigidbody()->AddForce(Velocity * DT);
	else
		GetOwner()->Rigidbody()->SetVelocity(Velocity);
}

void CPlyRun::BeginOverlap(CCollider3D* _Other)
{
}

void CPlyRun::OnOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER && KEY_PRESSED(KEY::E))
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}
