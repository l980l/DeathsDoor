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
	Stat tPrevStat = GetOwnerScript()->GetStat();
	m_iPrevHP = tPrevStat.HP;
	m_iOriginMaxHP = tPrevStat.Max_HP;

	GetOwner()->Animator3D()->Play(12, true);

	CSoundScript* pSoundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = pSoundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceShieldPrep.ogg", 1, 0.1f);
}

void CGrimKnightGuardStay::tick()
{
	GetOwner()->Rigidbody()->ClearForce();
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
	Stat tCurStat = GetOwnerScript()->GetStat();
	tCurStat.HP = m_iPrevHP;
	tCurStat.Max_HP = m_iOriginMaxHP;
	GetOwnerScript()->SetStat(tCurStat);
}
