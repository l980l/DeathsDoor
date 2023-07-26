#include "pch.h"
#include "CCrowHeadScript.h"

#include <Engine/CDetourMgr.h>

void CCrowHeadScript::begin()
{
	// �ִϸ��̼� ���.
	GetOwner()->Animator3D()->Play(0, true);

	// �÷��̾� ����.
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
		Vec3 newPos = currentPos + m_fSpeed * direction * DT;

		GetOwner()->Transform()->SetRelativePos(newPos);

		// ���� Ÿ�� ��ġ�� �����ߴٸ�, ���� ��� �ε���.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < m_fSpeed * DT)
		{
			++m_iCurrentPathIndex;
		}
	}

	// �÷��̾ �ٶ󺸴� ���.
	CDetourMgr::GetInst()->GetSmoothDirtoTarget(GetOwner());
}

void CCrowHeadScript::BeginOverlap(CCollider3D* _Other)
{
	// ���� �ε����ٸ� �о��
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(true);
	}

	// PlayerProjectile Layer�� ��ü�� �浹�� ���.
	if (_Other->GetOwner()->GetLayerIndex() == 4)
	{
		// �ݻ縦 �����Ѵٸ� �ݻ�ž� ��. �� ��� ���� �ð� ���� ������� ��. ��.. �ٵ� �ݻ縦 �ȸ���Ÿ� ���� �ð� ���� �˾Ƽ� ������� �ؾ߰ڳ�? ��... �ݻ縦 �Ѵٸ�, �ݻ� �� ��� ���� �ð� ���� ������� �ϰ�.
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
