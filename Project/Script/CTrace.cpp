#include "pch.h"
#include "CTrace.h"
#include "CMonsterScript.h"

#include <Engine/CDetourMgr.h>

CTrace::CTrace()
	: m_fLastRenewal(0.f)
	, m_fRenewal_Trace(2.f)
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
	float fSpeed = GetOwnerScript()->GetStat().Speed;

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
		// 다음 노드(메시) 위치
		Vec3 targetPos = m_vActualPath[m_iCurrentPathIndex];
		targetPos.z *= -1.f;
		if (targetPos.x == 0 && targetPos.y == 0 && targetPos.z == 0)
		{
			return;
		}
		// 현재 오브젝트 위치		
		Vec3 currentPos = GetOwner()->Transform()->GetWorldPos();

		// 이동할 방향 벡터 계산 및 정규화
		Vec3 direction = targetPos - currentPos;
		direction = direction.Normalize();

		// 새로운 위치 계산
		Vec3 newPos = currentPos + fSpeed * direction * DT;

		GetOwner()->Transform()->SetRelativePos(newPos);

		// 만약 타겟 위치에 도달했다면, 다음 경로 인덱스.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < fSpeed * DT)
		{
			++m_iCurrentPathIndex;
		}
	}
}

void CTrace::Enter()
{
	if (L"Bat" == GetOwner()->GetName())
	{
		Stat status = GetOwnerScript()->GetStat();
		GetOwner()->Animator3D()->Play(3, true);
	}
	else if (L"GrimKnight" == GetOwner()->GetName())
	{
		Stat status = GetOwnerScript()->GetStat();
		GetOwner()->Animator3D()->Play(6, true);
	}
	else if (L"Knight" == GetOwner()->GetName())
	{
		Stat status = GetOwnerScript()->GetStat();
		GetOwner()->Animator3D()->Play(1, true);
	}
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
