#include "pch.h"
#include "CStateScript.h"
#include "CGruntScript.h"
#include "GruntStates.h"

#include <Engine/CDetourMgr.h>

CGruntScript::CGruntScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::GRUNTSCRIPT)
	, m_fPlayerDistance(0.f)
	, m_fAttackRange(500.f)
	, m_iNailAttackCount(0)
	, m_bStarePlayer(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAttackRange, "AttackRange");
}

CGruntScript::CGruntScript(const CGruntScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::GRUNTSCRIPT)
	, m_fPlayerDistance(_Other.m_fPlayerDistance)
	, m_fAttackRange(_Other.m_fAttackRange)
	, m_iNailAttackCount(0)
	, m_bStarePlayer(false)
{
}

CGruntScript::~CGruntScript()
{
}

void CGruntScript::CountNailAttack()
{
	if (m_iNailAttackCount > 2)
		m_iNailAttackCount = 0;

	else
		++m_iNailAttackCount;
}

void CGruntScript::begin()
{
	CMonsterScript::begin();
	
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
		m_pStateScript->AddState(L"BackStep", new CGruntBackStep);
		m_pStateScript->AddState(L"Death", new CGruntDeath);
		m_pStateScript->AddState(L"Idle", new CGruntIdle);
		m_pStateScript->AddState(L"JumpAttack", new CGruntJumpAttack);
		m_pStateScript->AddState(L"JumpAttackReady", new CGruntJumpAttackReady);
		m_pStateScript->AddState(L"LeftMove", new CGruntLeftMove);
		m_pStateScript->AddState(L"Move", new CGruntMove);
		m_pStateScript->AddState(L"NailAttack", new CGruntNailAttack);
		m_pStateScript->AddState(L"NailAttackReady", new CGruntNailAttackReady);
		m_pStateScript->AddState(L"RightMove", new CGruntRightMove);
		m_pStateScript->AddState(L"Run", new CGruntRun);
		m_pStateScript->AddState(L"Run2", new CGruntRun2);
		m_pStateScript->AddState(L"Trace", new CGruntTrace);
		m_pStateScript->AddState(L"Walk", new CGruntWalk);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.Max_HP = 300;
		NewStat.HP = 300;
		NewStat.Attack = 50.f;
		NewStat.Attack_Speed = 1.f;
		NewStat.Speed = 1000.f;
		m_pStateScript->SetStat(NewStat);
	}
}

void CGruntScript::tick()
{
	CMonsterScript::tick();
	
	m_PlayerPos = GetPlayer()->Transform()->GetWorldPos();
	m_fPlayerDistance = GetDistance(m_PlayerPos, GetOwner()->Transform()->GetWorldPos());
	
	m_MonsterToPlayerDir = m_PlayerPos - Transform()->GetWorldPos();
	m_MonsterToPlayerDir.x /= m_fPlayerDistance;
	m_MonsterToPlayerDir.y /= m_fPlayerDistance;
	m_MonsterToPlayerDir.z /= m_fPlayerDistance;

	// 플레이어를 바라보는 경우.
	if (m_bStarePlayer)
	{
		CDetourMgr::GetInst()->GetSmoothDirtoTarget(GetOwner());
	}
}

void CGruntScript::BeginOverlap(CCollider3D* _Other)
{
	// 벽에 부딪힌다면 밀어내기
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(true);
	}

	// PlayerProjectile Layer의 물체와 충돌한 경우.
	if (_Other->GetOwner()->GetLayerIndex() == 4)
	{

	}

	// HP가 0 이하면 사망.
	if (m_pStateScript && m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}
}

void CGruntScript::OnOverlap(CCollider3D* _Other)
{
}

void CGruntScript::EndOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(false);
	}
}

void CGruntScript::SaveToLevelFile(FILE* _File)
{
}

void CGruntScript::LoadFromLevelFile(FILE* _File)
{
}
