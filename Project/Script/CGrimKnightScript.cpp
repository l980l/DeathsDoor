#include "pch.h"
#include "CGrimKnightScript.h"
#include "GrimKnightStates.h"
#include "CPlayerScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CRigidbody.h>
#include <Engine/CSound.h>
#include "CTrace.h"
#include "CStateScript.h"
#include "CSoundScript.h"

CGrimKnightScript::CGrimKnightScript()	
	: CMonsterScript((UINT)SCRIPT_TYPE::GRIMKNIGHTSCRIPT)
	, m_bRecognizeCheck(false)
	, m_bRetrace(false)
	, m_bOnCollision(false)
	, m_iHitCount(0)
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

	// �ʱ� ���� ����.
	Stat tInitStat;
	tInitStat.HP = 300;
	tInitStat.Max_HP = 300;
	tInitStat.Speed = 150.f;
	m_pStateScript->SetStat(tInitStat);
}

void CGrimKnightScript::tick()
{
	CMonsterScript::tick();

	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState()
			&& m_pStateScript->FindState(L"GuardStay") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}

	if (m_iHitCount >= 5 && m_pStateScript->GetCurState() == m_pStateScript->FindState(L"GuardStay"))
	{
		m_pStateScript->ChangeState(L"GuardBreak");
		m_iHitCount = 0;
	}
}

void CGrimKnightScript::CalcDir()
{
	m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
	Vec3 vCurDir = GetOwner()->Transform()->GetRelativeRot();
	GetOwner()->Transform()->SetRelativeRot(vCurDir.x, fDir, 0.f);
}

void CGrimKnightScript::BeginOverlap(CCollider3D* _Other)
{
	//4.��, ȭ��, ��, ��ź, ������ �浹�ϸ�
	if ((int)LAYER::PLAYER == _Other->GetOwner()->GetLayerIndex() && m_bOnCollision == false)
	{
		m_pStateScript->ChangeState(L"Attack");
		m_bOnCollision = true;
	}
	if ((int)LAYER::PLAYERPROJECTILE == _Other->GetOwner()->GetLayerIndex())
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
