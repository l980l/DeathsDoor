#include "pch.h"
#include "CLurkerScript.h"
#include "CStateScript.h"
#include "LurkerStates.h"

#include <Engine/CDetourMgr.h>

CLurkerScript::CLurkerScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::LURKERSCRIPT)
	, m_fPlayerDistance(0.f)
	, m_fBackStepRange(250.f)
	, m_fAttackRange(500.f)
	, m_bStarePlayer(false)
{
}

CLurkerScript::CLurkerScript(const CLurkerScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::LURKERSCRIPT)
	, m_fPlayerDistance(_Other.m_fPlayerDistance)
	, m_fAttackRange(_Other.m_fAttackRange)
	, m_bStarePlayer(false)
{
}

CLurkerScript::~CLurkerScript()
{
}

void CLurkerScript::begin()
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
		m_pStateScript->AddState(L"Attack", new CLurkerAttack);
		m_pStateScript->AddState(L"BackMove", new CLurkerBackMove);
		m_pStateScript->AddState(L"BackStep", new CLurkerBackStep);
		m_pStateScript->AddState(L"Death", new CLurkerDeath);
		m_pStateScript->AddState(L"FrontMove", new CLurkerFrontMove);
		m_pStateScript->AddState(L"Idle", new CLurkerIdle);
		m_pStateScript->AddState(L"LeftMove", new CLurkerLeftMove);
		m_pStateScript->AddState(L"Notify", new CLurkerNotify);
		m_pStateScript->AddState(L"RightMove", new CLurkerRightMove);
		m_pStateScript->AddState(L"Trace", new CLurkerTrace);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.HP = 300;
		NewStat.Attack = 50.f;
		NewStat.Attack_Speed = 1.f;
		NewStat.Speed = 500.f;
		m_pStateScript->SetStat(NewStat);
	}
}

void CLurkerScript::tick()
{
	m_PlayerPos = GetPlayer()->Transform()->GetWorldPos();
	m_fPlayerDistance = GetDistance(m_PlayerPos, GetOwner()->Transform()->GetWorldPos());

	m_MonsterToPlayerDir = m_PlayerPos - Transform()->GetWorldPos();
	m_MonsterToPlayerDir.x /= m_fPlayerDistance;
	m_MonsterToPlayerDir.y /= m_fPlayerDistance;
	m_MonsterToPlayerDir.z /= m_fPlayerDistance;

	// 플레이어를 바라보는 경우.
	if (m_bStarePlayer)
	{
		Vec3 CurRot = GetOwner()->Transform()->GetRelativeRot();
		GetOwner()->Transform()->SetRelativeRot(CurRot.x, CDetourMgr::GetInst()->GetSmoothDirtoTarget(GetOwner()), CurRot.z);
	}
}

void CLurkerScript::BeginOverlap(CCollider3D* _Other)
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

void CLurkerScript::OnOverlap(CCollider3D* _Other)
{
}

void CLurkerScript::EndOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(false);
	}
}

void CLurkerScript::SaveToLevelFile(FILE* _File)
{
}

void CLurkerScript::LoadFromLevelFile(FILE* _File)
{
}
