#include "pch.h"
#include "CCrowBossScript.h"
#include "CStateScript.h"
#include "CrowBossStates.h"
#include "CLevelSaveLoadInScript.h"
#include "CSoundScript.h"

#include <Engine/CDetourMgr.h>
#include <Engine/CPhysXMgr.h>

CCrowBossScript::CCrowBossScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::CROWBOSSSCRIPT)
	, m_fPlayerDistance(0.f)
	, m_bStarePlayer(false)
	, m_fPrevHP(0.f)
	, m_pCrowBossFeather(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_bDetect, "Detect");
}

CCrowBossScript::CCrowBossScript(const CCrowBossScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::CROWBOSSSCRIPT)
	, m_fPlayerDistance(0.f)
	, m_bStarePlayer(false)
	, m_fPrevHP(0.f)
	, m_pCrowBossFeather(nullptr)
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
		m_pStateScript->AddState(L"Walk",			new CCrowBossWalk);
		m_pStateScript->AddState(L"Stomp",			new CCrowBossStomp);
		m_pStateScript->AddState(L"StandingDeath",	new CCrowBossStandingDeath);
		m_pStateScript->AddState(L"Spitting",		new CCrowBossSpitting);
		m_pStateScript->AddState(L"Sliding",		new CCrowBossSliding);
		m_pStateScript->AddState(L"SlidingReady",	new CCrowBossSlidingReady);
		m_pStateScript->AddState(L"Run",			new CCrowBossRun);
		m_pStateScript->AddState(L"RightSpin",		new CCrowBossRightSpin);
		m_pStateScript->AddState(L"LeftSpin",		new CCrowBossLeftSpin);
		m_pStateScript->AddState(L"Jump",			new CCrowBossJump);
		m_pStateScript->AddState(L"Idle",			new CCrowBossIdle);
		m_pStateScript->AddState(L"GuidedBullet",	new CCrowBossGuidedBullet);
		m_pStateScript->AddState(L"Death",			new CCrowBossDeath);
		m_pStateScript->AddState(L"CutScene",		new CCrowBossCutScene);
		m_pStateScript->AddState(L"BatBullet",		new CCrowBossBatBullet);
		m_pStateScript->ChangeState(L"Idle");

		// 초기 스탯 설정.
		Stat NewStat;
		NewStat.Max_HP = 1000;
		NewStat.HP = NewStat.Max_HP;
		NewStat.Attack = 50.f;
		NewStat.Attack_Speed = 1.f;
		NewStat.Speed = 110.f;
		m_pStateScript->SetStat(NewStat);

		// 이전 HP
		m_fPrevHP = NewStat.Max_HP;
	}

	m_pCrowBossFeather = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\CrowBossFeather.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos());
}

void CCrowBossScript::tick()
{
	CMonsterScript::tick();

	// HP가 0 이하면 사망.
	if (m_pStateScript && m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
	}

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

	float fCurHP = m_pStateScript->GetStat().HP;

	// 체력이 줄었다면.
	if (m_fPrevHP < fCurHP)
	{
		// Sound
		CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\CrowBoss\\OldCrow_TakeDamage1.ogg", 1, 0.1f);

		m_fPrevHP = fCurHP;
	}

	m_pCrowBossFeather->Transform()->SetRelativePos(GetOwner()->Transform()->GetWorldPos());
}

void CCrowBossScript::BeginOverlap(CCollider3D* _Other)
{
	// 피격시 까마귀 머리 생성.
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::PLAYERPROJECTILE)
	{
		/*Vec3 CurPos = Transform()->GetWorldPos();

		Vec3 vDir = Transform()->GetXZDir();
		Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 100.f, CurPos.z) + vDir * 100.f;

		CGameObject* pGasGrenade = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\CrowHead.prefab", (int)LAYER::MONSTERPROJECTILE, vSpawnPos);
		CPhysXMgr::GetInst()->SetRigidPos(pGasGrenade->Rigidbody()->GetRigidbody(), vSpawnPos);*/
	}
}

void CCrowBossScript::OnOverlap(CCollider3D* _Other)
{
}

void CCrowBossScript::EndOverlap(CCollider3D* _Other)
{
}

void CCrowBossScript::SaveToLevelFile(FILE* _File)
{
}

void CCrowBossScript::LoadFromLevelFile(FILE* _File)
{
}

