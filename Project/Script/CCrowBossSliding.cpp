#include "pch.h"
#include "CCrowBossSliding.h"
#include "CCrowBossScript.h"
#include "CBossChainScript.h"

CCrowBossSliding::CCrowBossSliding()
	: m_qStartPos{}
	, m_qTargetPos{}
	, m_vCurTargetPos{}
	, m_vDirtoTarget{}
	, m_vRottoTarget{}
	, m_fSlidiingSpeed(1200.f)
	, m_bThrowmany(false)
	, m_iSliderCount(0)
{
}

CCrowBossSliding::~CCrowBossSliding()
{
}

void CCrowBossSliding::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);

	// ù ������ ����
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 vTargetPos = m_qTargetPos.front();
	m_vDirtoTarget = vTargetPos -  vCurPos;
	m_vDirtoTarget.Normalize();

	if (!m_qStartPos.empty())
	{
		Vec3 vStartPos = m_qStartPos.front();
		GetOwner()->Rigidbody()->SetRigidPos(vStartPos);
		m_qStartPos.pop();
		m_vDirtoTarget = m_qTargetPos.front() -  vStartPos;
		m_vDirtoTarget.Normalize();
	}
}

void CCrowBossSliding::tick()
{
	SlidingToTargetPos();
	ArriveToTarget();
}

void CCrowBossSliding::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
	m_iSliderCount = 0;
	m_vCurTargetPos = {};
	m_vDirtoTarget = {};
	m_vRottoTarget = {};
	queue<Vec3> empty = {};
	m_qStartPos.swap(empty);
	m_qTargetPos.swap(empty);
	m_bThrowmany = false;
}

void CCrowBossSliding::AddTargetPos(Vec3 _vTargetPos, Vec3 _vStartPos)
{
	if (abs(_vStartPos.x + _vStartPos.y) > 0.1f)
	{
		m_bThrowmany = false;
		m_qStartPos.push(_vStartPos);
	}

	m_qTargetPos.push(_vTargetPos);
	if(m_iSliderCount < 4)
		++m_iSliderCount;
}

void CCrowBossSliding::SlidingToTargetPos()
{
	Vec3 vVelocity = m_vDirtoTarget * m_fSlidiingSpeed;
	GetOwner()->Rigidbody()->SetVelocity(vVelocity);
	m_vecHook[m_iSliderCount]->GetScript<CBossChainScript>()->SetThrowStartPos(GetOwner()->Transform()->GetRelativePos());
}

void CCrowBossSliding::ArriveToTarget()
{
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	float fDiff = (m_qTargetPos.front() - vCurPos).Length();

	// �߰��� �������� ������ ������ �������� ������
	if (fDiff < 50.f)
	{
		--m_iSliderCount;
		m_qTargetPos.pop(); 		
		// TargetPos�� ���ٸ� �ٸ� �������� ��ȯ
		// �ƴ϶�� ������ �������� �ִ� �罽�� ��Ȱ��ȭ
		if (!m_qTargetPos.empty())
		{
			m_vDirtoTarget = m_qTargetPos.front() - vCurPos;
			m_vDirtoTarget.y = 0.f;
			m_vDirtoTarget.Normalize();

			if(m_bThrowmany)
			{
				GetOwner()->Rigidbody()->SetRigidPos(m_qStartPos.front());
				m_qStartPos.pop();
			}
			m_vecHook[m_iSliderCount]->GetScript<CBossChainScript>()->Active(false, 0.f);
		}
		else
		{
			ChangeState(L"RightSpin");
		}
	}	
}
