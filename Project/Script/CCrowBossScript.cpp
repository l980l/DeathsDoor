#include "pch.h"
#include "CCrowBossScript.h"
#include "CStateScript.h"
#include "CrowBossStates.h"

CCrowBossScript::CCrowBossScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::CROWBOSSSCRIPT)
	, m_fPlayerDistance(0.f)
{
}

CCrowBossScript::CCrowBossScript(const CCrowBossScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::CROWBOSSSCRIPT)
	, m_fPlayerDistance(0.f)
{
}

CCrowBossScript::~CCrowBossScript()
{
}

void CCrowBossScript::begin()
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
		NewStat.HP = 3000;
		m_pStateScript->SetStat(NewStat);
	}
}

void CCrowBossScript::tick()
{
}

void CCrowBossScript::BeginOverlap(CCollider3D* _Other)
{
}

void CCrowBossScript::SaveToLevelFile(FILE* _File)
{
}

void CCrowBossScript::LoadFromLevelFile(FILE* _File)
{
}

