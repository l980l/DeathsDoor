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
	, m_iThrowCount(0)
{
	if (m_vecHook.empty())
	{
		for (int i = 0; i < 5; ++i)
		{
			CGameObject* Hook = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BossHook.prefab", (int)LAYER::MONSTERPROJECTILE, Vec3(0.f, 0.f, 0.f));
			Hook->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
			Hook->GetScript<CBossChainScript>()->SetChainScript(this);
			Hook->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
			Hook->Collider3D()->SetAbsolute(true);
			Hook->Collider3D()->SetOffsetScale(Vec3(0.f));
			m_vecHook.push_back(Hook);

			vector<CGameObject*> vecChain;
			for (int j = 0; j < 40; ++j)
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
	GetOwner()->Animator3D()->Play(4, false);

	Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
	Vec3 vPlayerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
	Vec3 vDiff = vCurPos - vPlayerPos;

	// CrowBoss가 화면 밖에 있을 때는 사슬을 여러 개 던지게 함.
	if (vDiff.x > 900.f || vDiff.z > 500.f)
	{
		m_bThrowmany = true;

		// 랜덤으로 던지는 개수 설정
		if ((int)vDiff.x % 2 == 0)
		{
			// 십자 패턴
			m_iThrowCount = 2;
		}
		else
			// 대각선 패턴
			m_iThrowCount = 5;
	}
	else
		m_iThrowCount = 1;

	// Hooking State에 HookObj 등록
	CCrowBossSliding* pSlidingState = (CCrowBossSliding*)GetOwnerScript()->FindState(L"Sliding");
	for(size_t i = 0; i < m_vecHook.size(); ++i)
	{
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
	m_iThrowCount = 0;
}

void CCrowBossSlidingReady::ThrowHook()
{
	Vec3 vPlayerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
	if(1 == m_iThrowCount)
	{
		Vec3 vCurPos = GetOwner()->Transform()->GetWorldPos();
		Vec3 vDir = vPlayerPos - vCurPos;
		vDir.Normalize();
		float YRot = GetDir(Vec3(0.f), vPlayerPos);
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowStartPos(vCurPos);
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowDir(vCurPos);
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowRot(Vec3(0.f, YRot, 0.f));
		m_vecHook[0]->GetScript<CBossChainScript>()->SetThrowDistance(2500.f);
		m_vecHook[0]->GetScript<CBossChainScript>()->Active(true);		
	}
	else if (2 == m_iThrowCount)
	{
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

		for (int i = 0; i < m_iThrowCount; ++i)
		{
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowStartPos(vecThrowPos[i]);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDir(vecThrowDir[i]);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowRot(Vec3(0.f, GetDir(Vec3(0.f), vecThrowPos[i]), 0.f));
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDistance(2500.f);
			m_vecHook[i]->GetScript<CBossChainScript>()->Active(true, 0.3f * m_iThrowCount);
		}
	}
	else
	{
		for (int i = 0; i < m_iThrowCount; ++i)
		{
			float X = 200.f * i;
			float Z = 700.f;
			if (1 == i % 2)
			{
				i *= -1.f;
				Z *= -1.f;
			}

			Vec3 vDiff = Vec3(X, 0.f, Z);
			Vec3 vThrowPos = vPlayerPos - vDiff;
			Vec3 vThrowDir = vThrowPos - vPlayerPos;
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowStartPos(vThrowPos);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDir(vThrowDir);
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowRot(Vec3(0.f, GetDir(Vec3(0.f), vThrowPos), 0.f));
			m_vecHook[i]->GetScript<CBossChainScript>()->SetThrowDistance(2500.f);
			m_vecHook[i]->GetScript<CBossChainScript>()->Active(true, 0.3f * m_iThrowCount);
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
	m_bThrowReady = true;
}

void CCrowBossSlidingReady::SetPatern()
{
}
