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
		// 다음 노드(메시) 위치
		Vec3 targetPos = m_vActualPath[m_icurrentPathIndex];

		// 현재 오브젝트 위치		
		Vec3 currentPos = GetOwner()->Transform()->GetWorldPos();
		currentPos.z *= -1.f;

		// 이동할 방향 벡터 계산 및 정규화
		Vec3 direction = targetPos - currentPos;
		direction = direction.Normalize();

		// 새로운 위치 계산
		Vec3 newPos = currentPos + m_fSpeed * direction * DT;

		// 만약 타겟 위치에 도달했다면, 다음 경로 인덱스.
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
