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

	Transform()->SetRelativeScale(Vec3(0.35f));
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
		m_pStateScript->AddState(L"Idle", new CBatIdle);
		m_pStateScript->AddState(L"Recognize", new CBatRecognize);
		m_pStateScript->AddState(L"Trace", new CTrace);
		m_pStateScript->AddState(L"Attack", new CBatAttack);
		m_pStateScript->AddState(L"Death", new CBatDeath);
		m_pStateScript->ChangeState(L"Idle");
	}

	// �ʱ� ���� ����.
	Stat tInitStat;
	tInitStat.HP = 100;
	tInitStat.Max_HP = 100;
	tInitStat.Speed = 70.f;
	m_pStateScript->SetStat(tInitStat);
}

void CBatScript::tick()
{	
	CMonsterScript::tick();
	
	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	//2.HP�� 0 �̸� Death
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}
}

void CBatScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBatScript::SaveToLevelFile(FILE* _File)
{
}

void CBatScript::LoadFromLevelFile(FILE* _File)
{
}
