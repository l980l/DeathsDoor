#include "pch.h"
#include "CBazzokaMove.h"
#include "CBazookaScript.h"
#include <Engine/CDetourMgr.h>

void CBazzokaMove::Enter()
{
	m_fMoveTime = 0.f;
	GetOwner()->Animator3D()->Play(4, true);
}

void CBazzokaMove::tick()
{
	// Player ����
	GetOwner()->GetScript<CBazookaScript>()->SetStarePlayer(true);

	Vec3 PlayerPos = GetOwner()->GetScript<CBazookaScript>()->GetPlayerPos();

	float fDistance = GetOwner()->GetScript<CBazookaScript>()->GetPlayerDistance();

	// ���� ���� ������ Melee
	if (fDistance < GetOwner()->GetScript<CBazookaScript>()->GetMeleeRange())
	{
		ChangeState(L"Melee");
	}

	// ����. ���⼭�� �޸��� ���� �ٶ󺸵��� ȸ��������� �Ѵ�. 
	else if (fDistance <= GetOwner()->GetScript<CBazookaScript>()->GetRunAwayRange() || m_fMoveTime <= 0.5f)
	{
		m_fMoveTime += DT;
		
		GetOwner()->GetScript<CBazookaScript>()->SetStarePlayer(false);
		
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
			direction.Normalize();

			// ���ο� ��ġ ���
			Vec3 newPos = currentPos + direction * fSpeed * DT;
			direction.y = 0.f;

			GetOwner()->Rigidbody()->SetVelocity(direction * fSpeed);

			// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
			float distanceToTarget = (targetPos - currentPos).Length();
			if (distanceToTarget < 50.f)
			{
				++m_iCurrentPathIndex;
			}

			// ���� ���� �ٶ󺸵��� ȸ�� ��Ű��.
			Vec3 CurDir = GetOwner()->Transform()->GetRelativeRot();
			float fDir = GetSmoothDir(currentPos, targetPos, CurDir);
			GetOwner()->Transform()->SetRelativeRot(CurDir.x, fDir, 0.f);
		}
	}

	// ���ݹ���
	else if (fDistance < GetOwner()->GetScript<CBazookaScript>()->GetAttackRange() && fDistance > GetOwner()->GetScript<CBazookaScript>()->GetRunAwayRange())
	{
		ChangeState(L"Aim");
	}

	// ���� �̻��̸� Trace.
	else
	{
		ChangeState(L"Trace");
	}
}

void CBazzokaMove::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}

CBazzokaMove::CBazzokaMove()
	: m_fLastRenewal(0.f)
	, m_fRenewal_Trace(0.2f)
	, m_vActualPath{}
	, m_iActualPathCount(0)
	, m_iCurrentPathIndex(0)
	, m_fMoveTime(0.f)
{
}

CBazzokaMove::~CBazzokaMove()
{
}
