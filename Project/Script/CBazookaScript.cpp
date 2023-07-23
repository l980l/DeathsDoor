#include "pch.h"
#include "CBazookaScript.h"

#include "CStateScript.h"
#include "CBazookaAim.h"
#include "CBazzokaLongDistance.h"
#include "CBazzokaIdle.h"
#include "CBazzokaMelee.h"
#include "CBazzokaMove.h"
#include "CBazookaDeath.h"
#include "CTrace.h"

CBazookaScript::CBazookaScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::BAZOOKASCRIPT)
{
}

CBazookaScript::CBazookaScript(const CBazookaScript& _Other)
	: CMonsterScript((UINT)SCRIPT_TYPE::BAZOOKASCRIPT)
{
}

CBazookaScript::~CBazookaScript()
{
}

void CBazookaScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	// 상태 넣어주기.
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"Aim", new CBazookaAim);
		m_pStateScript->AddState(L"LongDistance", new CBazzokaLongDistance);
		m_pStateScript->AddState(L"Idle", new CBazzokaIdle);
		m_pStateScript->AddState(L"Melee", new CBazzokaMelee);
		m_pStateScript->AddState(L"Move", new CBazzokaMove);
		m_pStateScript->AddState(L"Death", new CBazookaDeath);
		m_pStateScript->AddState(L"Trace", new CTrace);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.HP = 300;
		m_pStateScript->SetStat(NewStat);
	}
}

void CBazookaScript::tick()
{
	// Death 상태라면 상태 교체 안함.
	if (m_pStateScript->GetCurState() == m_pStateScript->FindState(L"Death"))
		return;

	else 
	{
		m_pStateScript->ChangeState(L"Idle");
	}
}

void CBazookaScript::BeginOverlap(CCollider3D* _Other)
{
	// PlayerProjectile Layer의 물체와 충돌한 경우.
	if (_Other->GetOwner()->GetLayerIndex() == 4)
	{

	}

	// HP가 0 이하면 사망.
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}
}

void CBazookaScript::SaveToLevelFile(FILE* _File)
{
}

void CBazookaScript::LoadFromLevelFile(FILE* _File)
{
}
