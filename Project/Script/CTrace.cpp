#include "pch.h"
#include "CTrace.h"

#include <Engine/CDetourMgr.h>

CTrace::CTrace()
	: m_fLastRenewal(0.f)
	, m_fRenewal_Trace(2.f)
	, m_fSpeed(300.f)
	, m_vActualPath{}
	, m_iActualPathCount(0)
	, m_iCurrentPathIndex(0)
{
}

CTrace::~CTrace()
{ 
}

void CTrace::tick()
{
	m_fLastRenewal += DT;
	if (m_fLastRenewal >= m_fRenewal_Trace)
	{
		for (int i = 0; i < 256; ++i)
		{
			m_vActualPath[i] = Vec3(0.f, 0.f, 0.f);
		}
		m_iCurrentPathIndex = 0;
		m_iActualPathCount = 0;
		m_fLastRenewal -= m_fRenewal_Trace;
		Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
		memcpy(m_vActualPath, CDetourMgr::GetInst()->GetPathtoTarget(CurPos, &m_iActualPathCount), sizeof(Vec3) * 256);
	}

	if (m_iCurrentPathIndex < m_iActualPathCount)
	{
		// ���� ���(�޽�) ��ġ
		Vec3 targetPos = m_vActualPath[m_iCurrentPathIndex];
		targetPos.z *= -1.f;
		if (targetPos.x == 0 && targetPos.y == 0 && targetPos.z == 0)
		{
			return;
		}
		// ���� ������Ʈ ��ġ		
		Vec3 currentPos = GetOwner()->Transform()->GetWorldPos();

		// �̵��� ���� ���� ��� �� ����ȭ
		Vec3 direction = targetPos - currentPos;
		direction = direction.Normalize();

		// ���ο� ��ġ ���
		Vec3 newPos = currentPos + m_fSpeed * direction * DT;

		GetOwner()->Transform()->SetRelativePos(newPos);

		// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < m_fSpeed * DT)
		{
			++m_iCurrentPathIndex;
		}
	}
}

void CTrace::Enter()
{
}

void CTrace::Exit()
{
}

void CTrace::BeginOverlap(CCollider2D* _Other)
{
}

void CTrace::OnOverlap(CCollider2D* _Other)
{
}

void CTrace::EndOverlap(CCollider2D* _Other)
{
}