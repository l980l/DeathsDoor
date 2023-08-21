#include "pch.h"
#include "CBatScript.h"
#include "CPlayerScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CRigidbody.h>
#include "CTrace.h"
#include "CStateScript.h"
#include <Engine/CDetourMgr.h>
#include "BatStates.h"

CBatScript::CBatScript()	
	: CMonsterScript((UINT)SCRIPT_TYPE::BATSCRIPT)
	, m_bRecognizeCheck(false)
{
}

CBatScript::~CBatScript()
{
}

void CBatScript::begin()
{
	CMonsterScript::begin();

	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	// 상태 설정
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"BatIdle", new CBatIdle);
		m_pStateScript->AddState(L"BatRecognize", new CBatRecognize);
		m_pStateScript->AddState(L"BatTrace", new CTrace);
		m_pStateScript->AddState(L"BatAttack", new CBatAttack);
		m_pStateScript->AddState(L"BatDeath", new CBatDeath);

		m_pStateScript->ChangeState(L"BatIdle");
	}

	//Rigidbody 질량, 마찰, 마찰계수, 제한 속도 재 설정
	GetOwner()->Rigidbody()->SetVelocityLimit(100.f);

	// 초기 스탯 설정.
	Stat initStat;
	initStat.HP = 100;
	initStat.Max_HP = 100;
	initStat.Attack = 1;
	initStat.Attack_Speed = 10;
	initStat.Speed = 200;
	m_pStateScript->SetStat(initStat);
}

void CBatScript::tick()
{	
	CMonsterScript::tick();
	
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	if (m_bRecognizeCheck)
	{
		m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
		float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
		Vec3 vCurDir = GetOwner()->Transform()->GetRelativeRot();
		GetOwner()->Transform()->SetRelativeRot(vCurDir.x, fDir, 0.f);
	}

	//1.Player를 탐지했다면 Idle->exit()에서 Recognize --->Trace
	if (GetDetect()&& m_pStateScript->FindState(L"BatIdle") == m_pStateScript->GetCurState()&&
		m_bRecognizeCheck == false)
	{
		if (m_pStateScript->FindState(L"BatRecognize") != m_pStateScript->GetCurState())
		{
			m_pStateScript->ChangeState(L"BatRecognize");
			m_bRecognizeCheck = true;
		}
	}
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();
	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());
	if (fDistance > 100.f)
	{
		if (m_pStateScript->FindState(L"BatTrace") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"BatTrace");
	}
	//2.HP가 0 이면 Death
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"BatDeath") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"BatDeath");
	}
}

void CBatScript::BeginOverlap(CCollider3D* _Other)
{
	//4.검, 화살, 불, 폭탄, 갈고리와 충돌하면 Hit
	if (L"Player" == _Other->GetOwner()->GetName())
	{
		m_pStateScript->ChangeState(L"BatAttack");
	}
}

void CBatScript::SaveToLevelFile(FILE* _File)
{
}

void CBatScript::LoadFromLevelFile(FILE* _File)
{
}
