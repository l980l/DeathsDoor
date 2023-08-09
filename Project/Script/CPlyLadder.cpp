#include "pch.h"
#include "CPlyLadder.h"
#include "CPlayerScript.h"

CPlyLadder::CPlyLadder()
	: m_fSpeed(80.f)
	, m_fStartYPos(0.f)
	, m_fLadderHeight(0.f)
	, m_bEnd(false)
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
	// ��ٸ� �����Ⱑ �����ٸ� LadderFinish Anim ��� �� �����ٸ� Idle�� ��ȯ
	if (m_bEnd)
	{
		if (GetOwner()->Animator3D()->GetCurClip() != (int)PLAYERANIM_TYPE::LADDER_FINISH)
		{
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_FINISH, false);
		}
		else if (GetOwner()->Animator3D()->IsFinish())
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}

		return;
	}

	// �̵� �� Key�� Release�ƴٸ� Anim Stop
	if (!(KEY_RELEASE(KEY::W)) || !(KEY_RELEASE(KEY::S)))
	{
		GetOwner()->Animator3D()->SetStop(true);
	}

	// ��ٸ� ���� �̻����� �̵��ߴٸ� End��
	if (GetOwner()->Transform()->GetWorldPos().y - m_fStartYPos >= m_fLadderHeight)
	{
		m_bEnd = true;
	}
	
	// Ÿ�� ���� Dodge�� ��ȯ
	if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
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
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_UP, true);
	}
	else if (KEY_PRESSED(KEY::S))
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, -m_fSpeed * DT, 0.f));
		if (GetOwner()->Animator3D()->GetCurClip() != (int)PLAYERANIM_TYPE::LADDER_DOWN)
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_DOWN, true);
	}
}
