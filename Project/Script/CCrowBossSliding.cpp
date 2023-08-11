#include "pch.h"
#include "CCrowBossSliding.h"
#include "CCrowBossScript.h"
#include <Engine/CPhysXMgr.h>

CCrowBossSliding::CCrowBossSliding()
	: m_qStartPos{}
	, m_qTargetPos{}
	, m_vCurTargetPos{}
	, m_vDirtoTarget{}
	, m_vRottoTarget{}
	, m_fSlidiingSpeed(1500.f)
	, m_bThrowmany(false)
{
}

CCrowBossSliding::~CCrowBossSliding()
{
}

void CCrowBossSliding::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);

	// 첫 방향을 설정
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 vTargetPos = m_qTargetPos.front();
	m_vDirtoTarget = vTargetPos -  vCurPos;
	m_vDirtoTarget.Normalize();
}

void CCrowBossSliding::tick()
{
	SlidingToTargetPos();


}

void CCrowBossSliding::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}

void CCrowBossSliding::AddTargetPos(Vec3 _vTargetPos)
{
	m_bThrowmany = false;

	m_qTargetPos.push(_vTargetPos);
}

void CCrowBossSliding::AddStartTargetPos(Vec3 _vStartPos, Vec3 _vTargetPos)
{
	m_bThrowmany = true;

	m_qStartPos.push(_vStartPos);
	m_qTargetPos.push(_vTargetPos);
}

void CCrowBossSliding::SlidingToTargetPos()
{
	Vec3 vVelocity = m_vDirtoTarget * m_fSlidiingSpeed;
	GetOwner()->Rigidbody()->SetVelocity(vVelocity);
	ArriveToTarget();
}

void CCrowBossSliding::ArriveToTarget()
{
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	float fDiff = (m_qTargetPos.front() - vCurPos).Length();
	if (fDiff < 50.f)
	{
		m_qTargetPos.pop(); 
		
		if (!m_qTargetPos.empty())
		{
			m_vDirtoTarget = m_qTargetPos.front() - vCurPos;
			m_vDirtoTarget.Normalize();

			GetOwner()->Rigidbody()->SetRigidPos(m_qStartPos.front());
			m_qStartPos.pop();
		}
		else
		{
			ChangeState(L"RightSpin");
		}
	}

	
}
