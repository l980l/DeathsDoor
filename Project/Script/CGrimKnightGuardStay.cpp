#include "pch.h"
#include "CGrimKnightGuardStay.h"
#include "CSoundScript.h"
#include "CGrimKnightScript.h"
#include <Engine/CKeyMgr.h>
#include <Engine/CDetourMgr.h>

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
		
	Vec3 vCurDir = GetOwner()->Transform()->GetRelativeRot();
	vCurDir.y = CDetourMgr::GetInst()->GetDirtoTarget(GetOwner()->Transform()->GetWorldPos());
	GetOwner()->Transform()->SetRelativeRot(vCurDir);
}

void CGrimKnightGuardStay::Exit()
{
	Stat grimStat = GetOwnerScript()->GetStat();
	grimStat.HP = m_iPrevHP;
	grimStat.Max_HP = m_iOriginMaxHP;
	GetOwnerScript()->SetStat(grimStat);
}
