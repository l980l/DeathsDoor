#include "pch.h"
#include "CWalk.h"

CWalk::CWalk()
	: m_fSpeed(150.f)
{
}

CWalk::~CWalk()
{
}

void CWalk::tick()
{
	Move();

	// ������ �ִٸ�(���� �����Ӱ� ��ġ ���̰� ���ٸ�) Idle ��ȯ�ð� +
	if (Vec3(0.f, 0.f, 0.f) == GetOwner()->Transform()->GetWorldPos() - GetOwner()->Transform()->GetPrevPos())
		m_fTimeToIdle += DT;
	else
		m_fTimeToIdle = 0.f;

	// Idle ��ȯ�ð��� 0.1�� �Ѿ��ٸ� Idle��
	if (m_fTimeToIdle >= 0.1f)
		ChangeState(L"Idle");

}

void CWalk::Enter()
{
}

void CWalk::Exit()
{
}

void CWalk::Move()
{
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	float fSpeed = m_fSpeed;
	if (KEY_PRESSED(KEY::LSHIFT))
		fSpeed *= 5.f;

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * fSpeed;
	}

	GetOwner()->Transform()->SetRelativePos(vPos);
}

void CWalk::BeginOverlap(CCollider2D* _Other)
{
}

void CWalk::OnOverlap(CCollider2D* _Other)
{
}

void CWalk::EndOverlap(CCollider2D* _Other)
{
}
