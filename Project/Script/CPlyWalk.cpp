#include "pch.h"
#include "CPlyWalk.h"
#include "CPlayerScript.h"

CPlyWalk::CPlyWalk()
	: m_fSpeed(0.f)
	, m_fTimeToIdle(0.f)
	, m_bIce(false)
{
}

CPlyWalk::~CPlyWalk()
{
}

void CPlyWalk::Enter()
{
	m_fSpeed = GetOwnerScript()->GetStat().Speed * 0.5f;
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::WALK, false);
}

void CPlyWalk::tick()
{
	Move();
	// ������ �ִٸ�(���� �����Ӱ� ��ġ ���̰� ���ٸ�) Idle ��ȯ�ð� +
	if (Vec3(0.f, 0.f, 0.f) == GetOwner()->Transform()->GetWorldPos() - GetOwner()->Transform()->GetPrevPos())
	{
		m_fTimeToIdle += DT;
	}
	else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::D))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Run");
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
	else if (m_fTimeToIdle >= 0.03f)
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
	}
	else if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}
}

void CPlyWalk::Exit()
{
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
	m_fTimeToIdle = 0.f;
}

void CPlyWalk::Move()
{
	Vec3 Velocity = Vec3(0.f, 0.f, 0.f);

	if (KEY_PRESSED(KEY::W))
	{
		Velocity.z += 1.f;
	}

	if (KEY_PRESSED(KEY::S))
	{
		Velocity.z -= 1.f;
	}

	if (KEY_PRESSED(KEY::A))
	{
		Velocity.x -= 1.f;
	}

	if (KEY_PRESSED(KEY::D))
	{
		Velocity.x += 1.f;
	}
	Velocity.Normalize();

	Velocity *= m_fSpeed;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);
}

void CPlyWalk::BeginOverlap(CCollider3D* _Other)
{
}

void CPlyWalk::OnOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER && KEY_PRESSED(KEY::E))
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}

void CPlyWalk::EndOverlap(CCollider3D* _Other)
{
}
