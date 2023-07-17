#include "pch.h"
#include "CTrace.h"

#include <Engine/CDetourMgr.h>

CTrace::CTrace()
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
		m_fLastRenewal -= m_fRenewal_Trace;
		memcpy(m_vActualPath, CDetourMgr::GetInst()->GetPathtoTarget(GetOwner()->Transform()->GetWorldPos()), sizeof(Vec3) *256);
		m_icurrentPathIndex = 0;
	}

	if (m_icurrentPathIndex < m_iActualPathCount)
	{
		// ���� ���(�޽�) ��ġ
		Vec3 targetPos = m_vActualPath[m_icurrentPathIndex];

		// ���� ������Ʈ ��ġ		
		Vec3 currentPos = GetOwner()->Transform()->GetWorldPos();
		currentPos.z *= -1.f;

		// �̵��� ���� ���� ��� �� ����ȭ
		Vec3 direction = targetPos - currentPos;
		direction = direction.Normalize();

		// ���ο� ��ġ ���
		Vec3 newPos = currentPos + m_fSpeed * direction * DT;

		// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < m_fSpeed * DT)
		{
			m_icurrentPathIndex++;
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
