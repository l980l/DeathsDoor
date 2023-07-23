#include "pch.h"
#include "CBazzokaMove.h"
#include "CBazookaScript.h"
#include <Engine/CDetourMgr.h>

void CBazzokaMove::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CBazzokaMove::tick()
{
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();

	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());

	// 300 ���ϸ� Melee
	if (fDistance < 300.f)
	{
		ChangeState(L"Melee");
	}

	// 300 ~ 1000�̸� ����
	else if (fDistance < 1000)
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

			// ���� ��ġ���� �÷��̾���� ���̸�ŭ ������ ������ �̵���Ű��.
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 TargetPos = CurPos + CurPos - PlayerPos;

			memcpy(m_vActualPath, CDetourMgr::GetInst()->GetPathtoTarget(CurPos, TargetPos, &m_iActualPathCount), sizeof(Vec3) * 256);
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
			Vec3 newPos = currentPos + fSpeed * direction * DT;

			GetOwner()->Transform()->SetRelativePos(newPos);

			// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
			float distanceToTarget = (targetPos - newPos).Length();
			if (distanceToTarget < fSpeed * DT)
			{
				++m_iCurrentPathIndex;
			}
		}
	}

	// 1000 ~ 1500 ���̸� Aim
	else if (fDistance<1500.f)
	{
		ChangeState(L"Aim");
	}

	// 1500 �̻��̸� Trace
	else
	{
		ChangeState(L"Trace");
	}
}

void CBazzokaMove::Exit()
{
}

CBazzokaMove::CBazzokaMove()
	: m_fLastRenewal(0.f)
	, m_fRenewal_Trace(2.f)
	, m_vActualPath{}
	, m_iActualPathCount(0)
	, m_iCurrentPathIndex(0)
{
}

CBazzokaMove::~CBazzokaMove()
{
}
