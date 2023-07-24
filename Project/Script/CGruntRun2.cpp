#include "pch.h"
#include "CGruntRun2.h"
#include "CGruntScript.h"

#include <Engine/CDetourMgr.h>

void CGruntRun2::Enter()
{
	GetOwner()->Animator3D()->Play(8, true);
}

void CGruntRun2::tick()
{
	// ���ݹ��� �̳��� �÷��̾ ������ NailAttackReady.
	Vec3 PlayerPos = GetOwner()->GetScript<CGruntScript>()->GetPlayerPos();
	float fDistance = GetOwner()->GetScript<CGruntScript>()->GetPlayerDistance();

	// ���� ������ ���� ���. ���� ���� Ƚ���� ���� ���� ������ ���Ѵ�.
	if (fDistance < GetOwner()->GetScript<CGruntScript>()->GetAttackRange())
	{
		if (GetOwner()->GetScript<CGruntScript>()->GetNailAttackCount() < 2)
		{
			ChangeState(L"NailAttackReady");
			GetOwner()->GetScript<CGruntScript>()->CountNailAttack();
		}

		else
		{
			ChangeState(L"JumpAttackReady");
			GetOwner()->GetScript<CGruntScript>()->CountNailAttack();
		}
	}

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
}

void CGruntRun2::Exit()
{
}

CGruntRun2::CGruntRun2()
{
}

CGruntRun2::~CGruntRun2()
{
}
