#include "pch.h"
#include "CGrimKnightGuardStay.h"

void CGrimKnightGuardStay::tick()
{
	//5번 공격 받으면 Guard Break
	if (m_hitCount >= 5)
	{
		ChangeState(L"GuardBreak");
	}

	//Player가 오른쪽으로 이동하면 SpinRight
	//up방향과 (playerpos-monsterpos).Normalize을 외적하고. 이 값을 월드 벡터와 내적하였을 때 +면 오른쪽 -면 왼쪽
	Vec3 grimPos = GetOwner()->Transform()->GetWorldPos();
	CGameObject* player = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	Vec3 playerPos = player->Transform()->GetWorldPos();
	Vec3 vFront = GetOwner()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
	



	//Player가 왼쪽으로 이동하면 SpinLeft
}

float CGrimKnightGuardStay::GetDir(Vec3 _vStart, Vec3 _vTarget, bool _degree)
{
	// 아래축을 기준으로 CurPos에서 TargetPos를 바라보는 angle 반환
	Vec3 CurPos = _vStart;
	Vec2 vDefault = Vec2(0.f, -1.f);
	Vec3 TargetPos = _vTarget;
	Vec2 vDir = Vec2(TargetPos.x - CurPos.x, TargetPos.z - CurPos.z);
	vDir.Normalize();
	float angle = (float)acos(vDir.Dot(vDefault));

	if (vDir.x > 0.f)
		angle = (360.f / 180.f * XM_PI) - angle;

	if (_degree)
		angle *= (180.f / XM_PI);

	return angle;
}

void CGrimKnightGuardStay::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(12, true);
}

void CGrimKnightGuardStay::Exit()
{
}

void CGrimKnightGuardStay::BeginOverlap(CCollider2D* _Other)
{
	if (L"Sword" == _Other->GetOwner()->GetName())
	{
		m_hitCount++;
	}
	else if (L"Arrow" == _Other->GetOwner()->GetName())
	{
		m_hitCount++;
	}
	else if (L"Fire" == _Other->GetOwner()->GetName())
	{
		m_hitCount++;
	}
	else if (L"Bomb" == _Other->GetOwner()->GetName())
	{
		m_hitCount++;
	}
	else if (L"Hook" == _Other->GetOwner()->GetName())
	{
		m_hitCount++;
	}

}

void CGrimKnightGuardStay::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightGuardStay::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightGuardStay::CGrimKnightGuardStay()
{
}

CGrimKnightGuardStay::~CGrimKnightGuardStay()
{
}
