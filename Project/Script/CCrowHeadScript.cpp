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
	float fPlayerDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());

	Vec3 Dir;
	Dir = PlayerPos - Transform()->GetWorldPos();
	Dir.x /= fPlayerDistance;
	Dir.y /= fPlayerDistance;
	Dir.z /= fPlayerDistance;
	
	Vec3 Velocity = Dir;
	float fSpeed = 100.f;
	Velocity *= fSpeed * 10.f * DT;

	GetOwner()->Rigidbody()->AddVelocity(Velocity);

	float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
	Vec3 CurDir = GetOwner()->Transform()->GetRelativeRot();
	GetOwner()->Transform()->SetRelativeRot(CurDir.x, fDir, 0.f);
}

void CCrowHeadScript::BeginOverlap(CCollider3D* _Other)
{
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
