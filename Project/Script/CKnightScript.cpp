#include "pch.h"
#include "CKnightScript.h"

#include<Engine/CRigidbody.h>
#include "CTrace.h"
#include "CStateScript.h"

#include "KnightStates.h"



CKnightScript::CKnightScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::KNIGHTSCRIPT)
{
}

CKnightScript::CKnightScript(const CKnightScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::KNIGHTSCRIPT)
{
}

CKnightScript::~CKnightScript()
{
}

void CKnightScript::begin()
{
	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	// ���� ����
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"Idle", new CKnightIdle);
		m_pStateScript->AddState(L"Trace", new CTrace);
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

	//Rigidbody ����, ����, �������, ���� �ӵ� �� ����
	/*GetOwner()->Rigidbody()->SetMass(1.f);
	GetOwner()->Rigidbody()->SetFriction(1.f);
	GetOwner()->Rigidbody()->SetFrictionScale(1.f);*/
	GetOwner()->Rigidbody()->SetVelocityLimit(1.f);

	// �ʱ� ���� ����.
	m_stat.HP = 300;
	m_stat.Attack = 1;
	m_stat.Attack_Speed = 10;
	m_stat.Speed = 100;
	m_pStateScript->SetStat(m_stat);


	recognizeCheck = false;
	onCollision = false;
}

void CKnightScript::tick()
{
	//Player������ �ٶ󺸱�
	//Vec3 forward = GetOwner()->Transform()->GetWorldRotation().Forward();//������ �չ���

	if (GetDetect() && m_pStateScript->FindState(L"Idle") == m_pStateScript->GetCurState() &&
		recognizeCheck == false)
	{
		m_pStateScript->ChangeState(L"Trace");
		recognizeCheck = true;
	}
	else if (GetDetect() && m_pStateScript->FindState(L"SpinAttackCombo") == m_pStateScript->GetCurState())
	{
		m_pStateScript->ChangeState(L"Trace");
	}

	//HP�� 0 �̸� ��� ó��
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
		SetLifeSpan(0.5f);
	}
}

void CKnightScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Player" == _Other->GetOwner()->GetName())
	{
		m_pStateScript->ChangeState(L"RunAttack");
	}
	if (L"Sword" == _Other->GetName())
	{
		//ü��--
		//m_stat.HP -= SwordDamage
	}
	else if (L"Arrow" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Fire" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Bomb" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Hook" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Ghost" == _Other->GetName())
	{
		//ü��--
	}
}

void CKnightScript::SaveToLevelFile(FILE* _File)
{
}

void CKnightScript::LoadFromLevelFile(FILE* _File)
{
}
