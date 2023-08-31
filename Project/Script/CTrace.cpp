#include "pch.h"
#include "CTrace.h"
#include "CMonsterScript.h"
#include "CSoundScript.h"

#include <Engine/CDetourMgr.h>

CTrace::CTrace()
	: m_fLastRenewal(0.f)
	, m_fRenewal_Trace(0.3f)
	, m_vActualPath{}
	, m_iActualPathCount(0)
	, m_iCurrentPathIndex(0)
{
}

CTrace::~CTrace()
{
}

void CTrace::Enter()
{
	if (L"Bat" == GetOwner()->GetName())
	{
		GetOwner()->Animator3D()->Play(3, true);
	}
	else if (L"GrimKnight" == GetOwner()->GetName())
	{
		GetOwner()->Animator3D()->Play(6, true);

		CSoundScript* pSoundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = pSoundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceStep1.ogg", 1, 0.1f);
	}
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
		// ���� ���(�޽�) ��ġ
		Vec3 targetPos = m_vActualPath[m_iCurrentPathIndex];
		targetPos.z *= -1.f;
		if (targetPos.x == 0 && targetPos.y == 0 && targetPos.z == 0)
		{
			return;
		}
		// ���� ������Ʈ ��ġ		
		Vec3 vCurrentPos = GetOwner()->Transform()->GetWorldPos();

		// �̵��� ���� ���� ��� �� ����ȭ
		Vec3 vDirection = targetPos - vCurrentPos;
		vDirection.Normalize();

		// ���ο� ��ġ ���
		Vec3 newPos = vCurrentPos + vDirection * fSpeed * DT;
		vDirection.y = 0.f;

		GetOwner()->Rigidbody()->SetVelocity(vDirection * fSpeed);
		GetOwner()->Transform()->CalcDir();

		// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
		float distanceToTarget = (targetPos - vCurrentPos).Length();
		if (distanceToTarget < 50.f)
		{
			++m_iCurrentPathIndex;
		}
	}
	//sound
	if (GetOwner()->GetName() == L"GrimKnight" || GetOwner()->GetName() == L"Bat")
	{
		if ((GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos()
			- GetOwner()->Transform()->GetWorldPos()).Length() < 100.f)
			ChangeState(L"Attack");
	}
}

void CTrace::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}
