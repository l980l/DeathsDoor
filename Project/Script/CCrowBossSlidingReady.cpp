#include "pch.h"
#include "CCrowBossSlidingReady.h"
#include "CCrowBossScript.h"
#include "CCrowBossSliding.h"
#include "CBossChainScript.h"
#include "CLevelSaveLoadInScript.h"

CCrowBossSlidingReady::CCrowBossSlidingReady()
	: m_vecHook{}
	, m_bThrowmany(false)
	, m_bThrowReady(true)
	, m_tChainPatern()
	, m_iThrowCount(0)
{
	// 시작 시 Hook 및 Chain 생성
	if (m_vecHook.empty())
	{
		for (int i = 0; i < 5; ++i)
		{
			CGameObject* Hook = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BossHook.prefab", (int)LAYER::MONSTERPROJECTILE, Vec3(0.f, 0.f, 0.f));
			Hook->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
			Hook->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
			Hook->Collider3D()->SetAbsolute(true);
			Hook->Collider3D()->SetOffsetScale(Vec3(0.f));
			Hook->GetScript<CBossChainScript>()->SetChainScript(this);
			m_vecHook.push_back(Hook);

			vector<CGameObject*> vecChain;
			for (int j = 0; j < 70; ++j)
			{
				CGameObject* Chain = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\Chain.prefab", (int)LAYER::DEFAULT, Vec3(0.f, 0.f, 0.f));
				Chain->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
				vecChain.push_back(Chain);
				m_vecHook[i]->GetScript<CBossChainScript>()->SetChain(vecChain);
			}
		}
	}
}

CCrowBossSlidingReady::~CCrowBossSlidingReady()
{
}

void CCrowBossSlidingReady::Enter()
{
	Vec3 vPlayerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 vDiff = vCurPos - vPlayerPos;

	GetOwner()->Animator3D()->Play(4, false);

	// ===========================================
	// 테스트 용으로 패턴 고정 중, 추후 랜덤으로 수정할 것
	// ===========================================
	m_tChainPatern = CHAINPATERN::SPREAD;

	// Hooking State에 HookObj 등록
	CCrowBossSliding* pSlidingState = (CCrowBossSliding*)GetOwnerScript()->FindState(L"Sliding");
	for(size_t i = 0; i < m_vecHook.size(); ++i)
	{
		pSlidingState->SetHook(m_vecHook);
		m_vecHook[i]->GetScript<CBossChainScript>()->SetSlidingScript(pSlidingState);
	}

	ThrowHook();
}

void CCrowBossSlidingReady::tick()
{
}

void CCrowBossSlidingReady::Exit()
{
	m_bThrowmany = false;
	m_bThrowReady = true;
	m_tChainPatern = {};
	m_iThrowCount = 0;
}

void CCrowBossSlidingReady::ThrowHook()
{
	Vec3 vPlayerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
	if(CHAINPATERN::ONE == m_tChainPatern)
	{
		m_iThrowCount = 1;

		Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
		Vec3 vDir = vPlayerPos - vCurPos;
		vDir.y = 0.f;
		vDir.Normalize();
		float YRot = GetDir(Vec3(vCurPos), vPlayerPos);
		m_vecHook[0]->Transform()->SetRelativePos(vCurPos);
		m_vecHook[0]->Transform()->SetRelativeRot(Vec3(0.f, YRot, 0.f));
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowStartPos(vCurPos);
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowDir(vDir);
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowRot(Vec3(0.f, YRot, 0.f));
		m_vecHook[0]->GetScript<CBossChainScript>()->Active(true, false, 0.f);
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowDistance(3500.f);
	}
	else if (CHAINPATERN::CROSS == m_tChainPatern)
	{
		m_iThrowCount = 2;

		vector<Vec3> vecThrowPos, vecThrowDir = {};
		Vec3 vHrzThrowPos = Vec3(vPlayerPos.x - 1000.f, vPlayerPos.y, vPlayerPos.z);
		Vec3 vHrzDir = vPlayerPos - vHrzThrowPos;
		vHrzDir.Normalize();
		Vec3 vVtThrowPos = Vec3(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z - 800.f);
		Vec3 vVtDir = vPlayerPos - vVtThrowPos;
		vVtDir.Normalize();

		vecThrowPos.push_back(vHrzThrowPos);
		vecThrowDir.push_back(vHrzDir);

		vecThrowPos.push_back(vVtThrowPos);
		vecThrowDir.push_back(vVtDir);

		for (int i = 0; i < 2; ++i)
		{
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowStartPos(vecThrowPos[i]);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDir(vecThrowDir[i]);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowRot(Vec3(0.f, GetDir(Vec3(0.f), vecThrowPos[i]), 0.f));
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDistance(3500.f);
			m_vecHook[i]->GetScript<CBossChainScript>()->Active(true, true, 0.7f * i);
		}
	}
	else if (CHAINPATERN::SPREAD == m_tChainPatern)
	{
		m_iThrowCount = 5;

		for (int i = 0; i < 5; ++i)
		{
			float X = 300.f * i;
			float Z = 700.f;
			if (1 == i % 2)
			{
				X *= -1.f;
				Z *= -1.f;
			}

			Vec3 vDiff = Vec3(X, 0.f, Z);
			Vec3 vThrowPos = vPlayerPos - vDiff;
			Vec3 vThrowDir = vPlayerPos - vThrowPos;
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowStartPos(vThrowPos);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDir(vThrowDir);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowRot(Vec3(0.f, GetDir(Vec3(0.f), vThrowPos), 0.f));
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDistance(3500.f);
			m_vecHook[i]->GetScript<CBossChainScript>()->Active(true, true, 0.7f * i);
		}
	}
}

void CCrowBossSlidingReady::HookArrive()
{
	--m_iThrowCount;
	if (0 >= m_iThrowCount)
	{
		ChangeState(L"Sliding");
	}
}
