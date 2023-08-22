#include "pch.h"
#include "CGrimKnightGuardStay.h"
#include "CSoundScript.h"
#include "CGrimKnightScript.h"
#include <Engine/CKeyMgr.h>

CGrimKnightGuardStay::CGrimKnightGuardStay()
	: m_iHitCount(0)
	, m_iPrevHP(0)
	, m_iOriginMaxHP(0)
{
}

CGrimKnightGuardStay::~CGrimKnightGuardStay()
{
}

void CGrimKnightGuardStay::Enter()
{
	Stat grimStat = GetOwnerScript()->GetStat();
	m_iPrevHP = grimStat.HP;
	m_iOriginMaxHP = grimStat.Max_HP;
	grimStat.HP += 9999;
	grimStat.Max_HP += 9999;
	GetOwnerScript()->SetStat(grimStat);

	GetOwnerScript()->SetStat(grimStat);
	GetOwner()->Animator3D()->Play(12, true);

	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceShieldPrep.ogg", 1, 0.1);
}

void CGrimKnightGuardStay::tick()
{
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
	//5번 공격 받으면 Guard Break
	int a = GetOwner()->GetScript<CGrimKnightScript>()->GetHitCount();
	if (GetOwner()->GetScript<CGrimKnightScript>()->GetHitCount() >= 5)
	{
		ChangeState(L"GuardBreak");
	}
	
	if(KEY_TAP(KEY::R))
	{
		ChangeState(L"GuardBreak");
	}

	

	//Player가 오른쪽으로 이동하면 SpinRight
	//up방향과 (playerpos-monsterpos).Normalize을 외적하고. 이 값을 월드 벡터와 내적하였을 때 +면 오른쪽 -면 왼쪽
	Vec3 grimPos = GetOwner()->Transform()->GetWorldPos();
	CGameObject* player = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	Vec3 playerPos = player->Transform()->GetWorldPos();
	Vec3 vFront = GetOwner()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
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

void CGrimKnightGuardStay::Exit()
{
	Stat grimStat = GetOwnerScript()->GetStat();
	grimStat.HP = m_iPrevHP;
	grimStat.Max_HP = m_iOriginMaxHP;
	GetOwnerScript()->SetStat(grimStat);
}
