#include "pch.h"
#include "CKnightScript.h"

#include<Engine/CRigidbody.h>
#include "CTrace.h"
#include "CStateScript.h"

#include "KnightStates.h"


CKnightScript::CKnightScript() 
	: CMonsterScript((UINT)SCRIPT_TYPE::KNIGHTSCRIPT)
	, m_bRecognizeCheck(false)
{
}

CKnightScript::~CKnightScript()
{
}

void CKnightScript::begin()
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
		m_pStateScript->AddState(L"Idle", new CKnightIdle);
		m_pStateScript->AddState(L"Trace", new CKnightWalk);
		m_pStateScript->AddState(L"RunAttack", new CKnightRunAttack);
		m_pStateScript->AddState(L"CutScene", new CKnightCutScene);
		m_pStateScript->AddState(L"JumpReady", new CKnightJumpReady);
		m_pStateScript->AddState(L"JumpAttack1", new CKnightJumpAttack);
		m_pStateScript->AddState(L"JumpAttack2", new CKnightJumpAttack2);
		m_pStateScript->AddState(L"JumpFinish", new CKnightJumpFinish);
		m_pStateScript->AddState(L"ChopAttack", new CKnightChopAttack);
		m_pStateScript->AddState(L"ChopAttackEnd", new CKnightChopAttackEnd);
		m_pStateScript->AddState(L"ChopCombo", new CKnightChopAttackCombo);
		m_pStateScript->AddState(L"ChopComboEnd", new CKnightChopAttackComboEnd);
		m_pStateScript->AddState(L"SpinAttack", new CKnightSpinAttack);
		m_pStateScript->AddState(L"SpinAttackCombo", new CKnightSpinAttackCombo);
		m_pStateScript->AddState(L"Hit", new CKnightHit);
		m_pStateScript->AddState(L"Death", new CKnightDeath);

		m_pStateScript->ChangeState(L"Idle");
	}

	//Rigidbody 제한 속도 설정
	GetOwner()->Rigidbody()->SetVelocityLimit(150.f);

	// 초기 스탯 설정.
	Stat initStat;
	initStat.HP = 400;
	initStat.Max_HP = 400;
	initStat.Attack = 1;
	initStat.Attack_Speed = 10;
	initStat.Speed = 150;
	m_pStateScript->SetStat(initStat);
}

void CKnightScript::tick()
{
	CMonsterScript::tick();
	//Player방향을 바라보기
	m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
	Vec3 vCurDir = GetOwner()->Transform()->GetRelativeRot();
	GetOwner()->Transform()->SetRelativeRot(vCurDir.x, fDir, 0.f);

	if (GetDetect() && m_pStateScript->FindState(L"Idle") == m_pStateScript->GetCurState() &&
		m_bRecognizeCheck == false)
	{
		m_pStateScript->ChangeState(L"Trace");
		m_bRecognizeCheck = true;
	}
	else if (GetDetect() && m_pStateScript->FindState(L"SpinAttackCombo") == m_pStateScript->GetCurState())
	{
		m_pStateScript->ChangeState(L"Trace");
	}

	//HP가 0 이면 사망 처리
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}
}

void CKnightScript::BeginOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::PLAYER == _Other->GetOwner()->GetLayerIndex())
	{
		m_pStateScript->ChangeState(L"RunAttack");
	}
}

void CKnightScript::SaveToLevelFile(FILE* _File)
{
}

void CKnightScript::LoadFromLevelFile(FILE* _File)
{
}
