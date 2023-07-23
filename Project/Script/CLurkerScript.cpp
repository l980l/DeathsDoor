#include "pch.h"
#include "CLurkerScript.h"
#include "CStateScript.h"

#include "CLurkerAttack.h"
#include "CLurkerBackMove.h"
#include "CLurkerBackStep.h"
#include "CLurkerDeath.h"
#include "CLurkerFrontMove.h"
#include "CLurkerIdle.h"
#include "CLurkerLeftMove.h"
#include "CLurkerNotify.h"
#include "CLurkerRightMove.h"
#include "CTrace.h"

void CLurkerScript::begin()
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
		m_pStateScript->AddState(L"Attack", new CLurkerAttack);
		m_pStateScript->AddState(L"BackMove", new CLurkerBackMove);
		m_pStateScript->AddState(L"BackStep", new CLurkerBackStep);
		m_pStateScript->AddState(L"Death", new CLurkerDeath);
		m_pStateScript->AddState(L"FrontMove", new CLurkerFrontMove);
		m_pStateScript->AddState(L"Idle", new CLurkerIdle);
		m_pStateScript->AddState(L"LeftMove", new CLurkerLeftMove);
		m_pStateScript->AddState(L"Notify", new CLurkerNotify);
		m_pStateScript->AddState(L"RightMove", new CLurkerRightMove);
		m_pStateScript->AddState(L"Trace", new CTrace);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.HP = 300;
		m_pStateScript->SetStat(NewStat);
	}
}

void CLurkerScript::tick()
{
	// Death 상태라면 상태 교체 안함.
	if (m_pStateScript->GetCurState() == m_pStateScript->FindState(L"Death"))
		return;

	else
	{
		m_pStateScript->ChangeState(L"Idle");
	}
}

void CLurkerScript::BeginOverlap(CCollider3D* _Other)
{
}

void CLurkerScript::SaveToLevelFile(FILE* _File)
{
}

void CLurkerScript::LoadFromLevelFile(FILE* _File)
{
}

CLurkerScript::CLurkerScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::LURKERSCRIPT)
{
}

CLurkerScript::CLurkerScript(const CLurkerScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::LURKERSCRIPT)
{
}

CLurkerScript::~CLurkerScript()
{
}
