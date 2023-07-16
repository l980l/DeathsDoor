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

	}

	if (currentPathIndex < m_iactualPathCount)
	{
		// ���� ���(�޽�) ��ġ
		Vec3 targetPos(actualPath[3 * currentPathIndex], actualPath[3 * currentPathIndex + 1], actualPath[3 * currentPathIndex + 2]);

		// ���� ������Ʈ ��ġ		
		Vec3 currentPos = Vec3(_vStartPos.x, _vStartPos.y, -_vStartPos.z);

		// �̵��� ���� ���� ��� �� ����ȭ
		Vec3 direction = targetPos - currentPos;
		direction = direction.Normalize();

		// ���ο� ��ġ ���
		Vec3 newPos = currentPos + speed * direction * DT;

		// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < speed * DT)
		{
			currentPathIndex++;
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
