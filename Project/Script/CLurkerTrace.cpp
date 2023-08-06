#include "pch.h"
#include "CLurkerTrace.h"
#include "CLurkerScript.h"

#include <Engine/CDetourMgr.h>

void CLurkerTrace::Enter()
{
	GetOwner()->Animator3D()->Play(2, true);
}

void CLurkerTrace::tick()
{
	Vec3 PlayerPos = GetOwner()->GetScript<CLurkerScript>()->GetPlayerPos();
	float fDistance = GetOwner()->GetScript<CLurkerScript>()->GetPlayerDistance();

	// 공격 범위에 들어온 경우. 
	if (fDistance < GetOwner()->GetScript<CLurkerScript>()->GetAttackRange())
		ChangeState(L"Notify");

	else
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
			direction.Normalize();

			// 새로운 위치 계산
			Vec3 newPos = currentPos + direction * fSpeed * DT;
			direction.y = 0.f;

			GetOwner()->Rigidbody()->SetVelocity(direction * fSpeed);

			// 만약 타겟 위치에 도달했다면, 다음 경로 인덱스.
			float distanceToTarget = (targetPos - currentPos).Length();
			if (distanceToTarget < 50.f)
			{
				++m_iCurrentPathIndex;
			}
		}
	}
}

void CLurkerTrace::Exit()
{
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f));
}

void CLurkerTrace::BeginOverlap(CCollider3D* _Other)
{
}

void CLurkerTrace::OnOverlap(CCollider3D* _Other)
{
}

void CLurkerTrace::EndOverlap(CCollider3D* _Other)
{
}

CLurkerTrace::CLurkerTrace()
	: m_fLastRenewal(0.f)
	, m_fRenewal_Trace(2.f)
	, m_vActualPath{}
	, m_iActualPathCount(0)
	, m_iCurrentPathIndex(0)
{
}

CLurkerTrace::~CLurkerTrace()
{
}
