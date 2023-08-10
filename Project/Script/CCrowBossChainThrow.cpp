#include "pch.h"
#include "CCrowBossChainThrow.h"
#include "CLevelSaveLoadInScript.h"
#include "CBossChainScript.h"

CCrowBossChainThrow::CCrowBossChainThrow()
	: m_pHook(nullptr)
	, m_vecChain{}
{
	if (nullptr == m_pHook)
	{
		m_pHook = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BossHook.prefab", (int)LAYER::PLAYERPROJECTILE, Vec3(0.f, 0.f, 0.f));
		m_pHook->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		//m_pHook->GetScript<CBossChainScript>()->SetChainScript(this);
		m_pHook->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
		m_pHook->Collider3D()->SetAbsolute(true);
		m_pHook->Collider3D()->SetOffsetScale(Vec3(0.f));
	}
	if (m_vecChain.empty())
	{
		for (int i = 0; i < 80; ++i)
		{
			CGameObject* Chain = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BossChain.prefab", (int)LAYER::DEFAULT, Vec3(0.f, 0.f, 0.f));
			Chain->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
			m_vecChain.push_back(Chain);
			//m_pHook->GetScript<CBossChainScript>()->SetChain(m_vecChain);
		}
	}
}

CCrowBossChainThrow::~CCrowBossChainThrow()
{
}

void CCrowBossChainThrow::Enter()
{
}

void CCrowBossChainThrow::tick()
{
}

void CCrowBossChainThrow::Exit()
{
}
