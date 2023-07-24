#include "pch.h"
#include "CBatIdle.h"

CBatIdle::CBatIdle()
{
}

CBatIdle::~CBatIdle()
{
}

void CBatIdle::tick()
{
	m_fTime += DT;

	Stat m_stat = GetOwnerScript()->GetStat();
	if (0.f<=m_fTime && m_fTime < 0.4f)
	{
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(m_stat.Speed * DT, 0.f, m_stat.Speed * DT));
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(0.f, 0.f, m_stat.Speed * DT));
	}
	else if (0.4f <= m_fTime && m_fTime < 0.8f)
	{
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(-m_stat.Speed * DT, 0.f, m_stat.Speed * DT));
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(-m_stat.Speed * DT, 0.f, 0.f));
	}
	else if (0.8f <= m_fTime && m_fTime < 1.2f)
	{
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(-m_stat.Speed * DT, 0.f, -m_stat.Speed * DT));
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(0.f, 0.f, -m_stat.Speed * DT));
	}
	else if (1.2f <= m_fTime && m_fTime < 1.6f)
	{
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(m_stat.Speed * DT, 0.f, -m_stat.Speed * DT));
		GetOwnerScript()->GetOwner()->Rigidbody()->AddVelocity(Vec3(m_stat.Speed * DT, 0.f, 0.f));
	}
	else if(1.6f<=m_fTime)
		m_fTime = 0.f;
}

void CBatIdle::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
}

void CBatIdle::Exit()
{
}

void CBatIdle::BeginOverlap(CCollider2D* _Other)
{
}

void CBatIdle::OnOverlap(CCollider2D* _Other)
{
}

void CBatIdle::EndOverlap(CCollider2D* _Other)
{
}
