#include "pch.h"
#include "CCrowHeadScript.h"

#include <Engine/CDetourMgr.h>

void CCrowHeadScript::begin()
{
	// 애니메이션 재생.
	GetOwner()->Animator3D()->Play(0, true);

	// 플레이어 설정.
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	}
}

void CCrowHeadScript::tick()
{
	Vec3 PlayerPos = m_pPlayer->Transform()->GetWorldPos();

	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());

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
		Vec3 newPos = currentPos + m_fSpeed * direction * DT;

		GetOwner()->Transform()->SetRelativePos(newPos);

		// 만약 타겟 위치에 도달했다면, 다음 경로 인덱스.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < m_fSpeed * DT)
		{
			++m_iCurrentPathIndex;
		}
	}

	// 플레이어를 바라보는 경우.
	CDetourMgr::GetInst()->GetSmoothDirtoTarget(GetOwner());
}

void CCrowHeadScript::BeginOverlap(CCollider3D* _Other)
{
	// 벽에 부딪힌다면 밀어내기
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(true);
	}

	// PlayerProjectile Layer의 물체와 충돌한 경우.
	if (_Other->GetOwner()->GetLayerIndex() == 4)
	{
		// 반사를 구현한다면 반사돼야 함. 이 경우 일정 시간 이후 사라져야 함. 음.. 근데 반사를 안만들거면 일정 시간 이후 알아서 사라지게 해야겠네? 흠... 반사를 한다면, 반사 된 경우 일정 시간 이후 사라지게 하고.
	}
}

void CCrowHeadScript::OnOverlap(CCollider3D* _Other)
{
}

void CCrowHeadScript::EndOverlap(CCollider3D* _Other)
{
}

CCrowHeadScript::CCrowHeadScript()
	: CScript((UINT)SCRIPT_TYPE::CROWHEADSCRIPT)
	, m_pPlayer(nullptr)
	, m_fSpeed(500.f)
{
}

CCrowHeadScript::CCrowHeadScript(const CCrowHeadScript& _Other)
	: CScript((UINT)SCRIPT_TYPE::CROWHEADSCRIPT)
	, m_pPlayer(_Other.m_pPlayer)
	, m_fSpeed(_Other.m_fSpeed)
{
}

CCrowHeadScript::~CCrowHeadScript()
{
}
