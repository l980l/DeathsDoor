#include "pch.h"
#include "CCrowBossScript.h"
#include "CStateScript.h"
#include "CrowBossStates.h"

#include <Engine/CDetourMgr.h>

CCrowBossScript::CCrowBossScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::CROWBOSSSCRIPT)
	, m_fPlayerDistance(0.f)
	, m_bStarePlayer(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_bDetect, "Detect");
}

CCrowBossScript::CCrowBossScript(const CCrowBossScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::CROWBOSSSCRIPT)
	, m_fPlayerDistance(0.f)
	, m_bStarePlayer(false)
{
}

CCrowBossScript::~CCrowBossScript()
{
}

void CCrowBossScript::begin()
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
		m_pStateScript->AddState(L"Walk", new CCrowBossWalk);
		m_pStateScript->AddState(L"Stomp", new CCrowBossStomp);
		m_pStateScript->AddState(L"StandingDeath", new CCrowBossStandingDeath);
		m_pStateScript->AddState(L"Spitting", new CCrowBossSpitting);
		m_pStateScript->AddState(L"SlidingReady", new CCrowBossSlidingReady);
		m_pStateScript->AddState(L"Sliding", new CCrowBossSliding);
		m_pStateScript->AddState(L"Run", new CCrowBossRun);
		m_pStateScript->AddState(L"RightSpin", new CCrowBossRightSpin);
		m_pStateScript->AddState(L"LeftSpin", new CCrowBossLeftSpin);
		m_pStateScript->AddState(L"Jump", new CCrowBossJump);
		m_pStateScript->AddState(L"Idle", new CCrowBossIdle);
		m_pStateScript->AddState(L"GuidedBullet", new CCrowBossGuidedBullet);
		m_pStateScript->AddState(L"Death", new CCrowBossDeath);
		m_pStateScript->AddState(L"CutScene", new CCrowBossCutScene);
		m_pStateScript->AddState(L"BatBullet", new CCrowBossBatBullet);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.Max_HP = 3000;
		NewStat.HP = 3000;
		NewStat.Attack = 50.f;
		NewStat.Attack_Speed = 1.f;
		NewStat.Speed = 150.f;
		m_pStateScript->SetStat(NewStat);
	}
}

void CCrowBossScript::tick()
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
		float fDir = GetSmoothDir(GetOwner(), m_pPlayer);
		Vec3 CurDir = GetOwner()->Transform()->GetRelativeRot();
		GetOwner()->Transform()->SetRelativeRot(CurDir.x, fDir, 0.f);
	}
}

void CCrowBossScript::BeginOverlap(CCollider3D* _Other)
{
	// 벽에 부딪힌다면 밀어내기
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(true);
	}

	// HP가 0 이하면 사망.
	if (m_pStateScript && m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}
}

void CCrowBossScript::OnOverlap(CCollider3D* _Other)
{
}

void CCrowBossScript::EndOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(false);
	}
}

void CCrowBossScript::SaveToLevelFile(FILE* _File)
{
}

void CCrowBossScript::LoadFromLevelFile(FILE* _File)
{
}

