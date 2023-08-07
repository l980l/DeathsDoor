#include "pch.h"
#include "CBazookaScript.h"
#include "CStateScript.h"
#include "BazookaStates.h"

#include <Engine/CDetourMgr.h>

CBazookaScript::CBazookaScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::BAZOOKASCRIPT)
	, m_fPlayerDistance(0.f)
	, m_fMeleeRange(300.f)
	, m_fRunAwayRange(600.f)
	, m_fAttackRange(1000.f)
	, m_bStarePlayer(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fMeleeRange, "MeleeRange");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fRunAwayRange, "RunAwayRange");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAttackRange, "AttackRange");
}

CBazookaScript::CBazookaScript(const CBazookaScript& _Other)
	: CMonsterScript((UINT)SCRIPT_TYPE::BAZOOKASCRIPT)
	, m_fPlayerDistance(_Other.m_fPlayerDistance)
	, m_fMeleeRange(_Other.m_fMeleeRange)
	, m_fRunAwayRange(_Other.m_fRunAwayRange)
	, m_fAttackRange(_Other.m_fAttackRange)
	, m_bStarePlayer(false)
{
}

CBazookaScript::~CBazookaScript()
{
}

void CBazookaScript::begin()
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
		m_pStateScript->AddState(L"Aim", new CBazookaAim);
		m_pStateScript->AddState(L"LongDistance", new CBazzokaLongDistance);
		m_pStateScript->AddState(L"Idle", new CBazzokaIdle);
		m_pStateScript->AddState(L"Melee", new CBazzokaMelee);
		m_pStateScript->AddState(L"Move", new CBazzokaMove);
		m_pStateScript->AddState(L"Death", new CBazookaDeath);
		m_pStateScript->AddState(L"Trace", new CBazookaTrace);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.Max_HP = 300;
		NewStat.HP = 300;
		NewStat.Attack = 50.f;
		NewStat.Attack_Speed = 1.f;
		NewStat.Speed = 100.f;
		m_pStateScript->SetStat(NewStat);
	}
}

void CBazookaScript::tick()
{
	CMonsterScript::tick();
	
	m_PlayerPos = GetPlayer()->Transform()->GetWorldPos();
	m_fPlayerDistance = GetDistance(m_PlayerPos, Transform()->GetWorldPos());

	m_MonsterToPlayerDir = m_PlayerPos - Transform()->GetWorldPos();
	m_MonsterToPlayerDir.x /= m_fPlayerDistance;
	m_MonsterToPlayerDir.y /= m_fPlayerDistance;
	m_MonsterToPlayerDir.z /= m_fPlayerDistance;

	// 플레이어를 바라보는 경우.
	if (m_bStarePlayer)
	{
		float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
		Vec3 CurDir = GetOwner()->Transform()->GetRelativeRot();
		GetOwner()->Transform()->SetRelativeRot(CurDir.x, fDir, 0.f);
	}
}

void CBazookaScript::BeginOverlap(CCollider3D* _Other)
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

void CBazookaScript::OnOverlap(CCollider3D* _Other)
{
}

void CBazookaScript::EndOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(false);
	}
}

void CBazookaScript::SaveToLevelFile(FILE* _File)
{
}

void CBazookaScript::LoadFromLevelFile(FILE* _File)
{
}
