#include "pch.h"
#include "CGrimKnightScript.h"
#include "CPlayerScript.h"

#include <Engine/CGameObject.h>
#include<Engine/CRigidbody.h>
#include "CTrace.h"
#include "CStateScript.h"
#include "CSoundScript.h"
#include <Engine/CSound.h>
#include "GrimKnightStates.h"



CGrimKnightScript::CGrimKnightScript()	:
	CMonsterScript((UINT)SCRIPT_TYPE::GRIMKNIGHTSCRIPT)
	, m_bRecognizeCheck(false)
	, m_bRetrace(false)
	, m_bOnCollision(false)
	, m_iHitCount(0)
{
}

CGrimKnightScript::CGrimKnightScript(const CGrimKnightScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::GRIMKNIGHTSCRIPT)
{
}

CGrimKnightScript::~CGrimKnightScript()
{
}

void CGrimKnightScript::begin()
{
	CMonsterScript::begin();

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
		m_pStateScript->AddState(L"Idle", new CGrimKnightIdle);
		m_pStateScript->AddState(L"Trace", new CTrace);
		m_pStateScript->AddState(L"Attack", new CGrimKnightMelee);
		m_pStateScript->AddState(L"SpinDown", new CGrimKnightSpinDown);
		m_pStateScript->AddState(L"SpinUp", new CGrimKnightSpinUp);
		m_pStateScript->AddState(L"LongDistance", new CGrimKnightLongDistance);
		m_pStateScript->AddState(L"BackStep1", new CGrimKnightBackStep);
		m_pStateScript->AddState(L"BackStep2", new CGrimKnightBackStep2);
		m_pStateScript->AddState(L"Guard", new CGrimKnightGuard);
		m_pStateScript->AddState(L"GuardStay", new CGrimKnightGuardStay);
		m_pStateScript->AddState(L"GuardBreak", new CGrimKnightGuardBreak);
		m_pStateScript->AddState(L"Death", new CGrimKnightDeath);

		m_pStateScript->ChangeState(L"Idle");
	}

	//Rigidbody ����, ����, �������, ���� �ӵ� �� ����
	GetOwner()->Rigidbody()->SetVelocityLimit(200.f);

	// �ʱ� ���� ����.
	Stat initStat;
	initStat.HP = 300;
	initStat.Max_HP = 300;
	initStat.Attack = 1;
	initStat.Attack_Speed = 10;
	initStat.Speed = 300;
	m_pStateScript->SetStat(initStat);
}

void CGrimKnightScript::tick()
{
	CMonsterScript::tick();
	//���� �÷��̾� Ž�� -> ����
	if (GetDetect() && m_pStateScript->FindState(L"Idle") == m_pStateScript->GetCurState() &&
		m_bRecognizeCheck == false)
	{
		m_bRecognizeCheck = true;
		m_pStateScript->ChangeState(L"Trace");
	}
	
	if (m_pStateScript->GetCurState() == m_pStateScript->FindState(L"GuardBreak"))
	{
		m_iHitCount = 0;
	}

	m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
	Vec3 vCurDir = GetOwner()->Transform()->GetRelativeRot();
	GetOwner()->Transform()->SetRelativeRot(vCurDir.x, fDir, 0.f);

	if (GetDetect() && m_pStateScript->FindState(L"LongDistance") == m_pStateScript->GetCurState()
		&& !m_bRecognizeCheck)
	{
		m_pStateScript->ChangeState(L"Trace");
	}

	//2.HP�� 0 �̸� Death
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}
}

void CGrimKnightScript::BeginOverlap(CCollider3D* _Other)
{
	//4.��, ȭ��, ��, ��ź, ������ �浹�ϸ�
	if (L"Player" == _Other->GetOwner()->GetName() && m_bOnCollision == false)
	{
		m_pStateScript->ChangeState(L"Attack");
		m_bOnCollision = true;
	}
	if (L"Slash_R" == _Other->GetOwner()->GetName())
	{
		if(m_pStateScript->GetCurState() == m_pStateScript->FindState(L"GuardStay"))
			m_iHitCount++;
	}
	else if (L"Slash_L" == _Other->GetOwner()->GetName())
	{
		if(m_pStateScript->GetCurState() == m_pStateScript->FindState(L"GuardStay"))
			m_iHitCount++;
	}

	else if (L"Ghost" == _Other->GetName())
	{
		//ü��--
	}
}

void CGrimKnightScript::OnOverlap(CCollider3D* _Other)
{
}

void CGrimKnightScript::EndOverlap(CCollider3D* _Other)
{
}

void CGrimKnightScript::SaveToLevelFile(FILE* _File)
{

}

void CGrimKnightScript::LoadFromLevelFile(FILE* _File)
{
}
