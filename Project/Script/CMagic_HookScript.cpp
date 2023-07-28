#include "pch.h"
#include "CMagic_HookScript.h"
#include "CPlyMagic_Hook.h"
#include "CLevelSaveLoadInScript.h"

CMagic_HookScript::CMagic_HookScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_HOOKSCRIPT)
	, m_pOwner(nullptr)
	, m_vecChain{}
	, m_vStartPos{}
	, m_vThrownDir{}
	, m_fTime(0.f)
	, m_fDistancetoTarget(0.f)
	, m_fChainSpacing(0.f)
	, m_bSnatch(false)
	, m_bReturn(false)
{	
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDistancetoTarget, "Distance");
	AddScriptParam(SCRIPT_PARAM::VEC3, m_vStartPos, "StartPos");
	AddScriptParam(SCRIPT_PARAM::VEC3, m_vThrownDir, "ThrownDir");
}

CMagic_HookScript::~CMagic_HookScript()
{
	for (int i = 0; i < 80; ++i)
	{
		if(nullptr != m_vecChain[i])
		m_vecChain[i]->SetLifeSpan(0.f);
		m_vecChain[i] = nullptr;
	}
	
}

void CMagic_HookScript::begin()
{
	m_fChainSpacing = 30.f;
	m_vThrownDir.y = 0.f;
	m_vThrownDir.Normalize();

	if (m_vecChain.empty() )
	{
		CLevelSaveLoadInScript script;
		for (int i = 0; i < 80; ++i)
		{
			Vec3 SpawnPos = m_vStartPos +  m_vThrownDir * (m_fChainSpacing * (i + 1));
			CGameObject* Chain = script.SpawnandReturnPrefab(L"prefab\\Chain.prefab", (int)LAYER::DEFAULT, SpawnPos);
			float YDir = GetDir(Vec3(0.f, 0.f, 0.f), m_vThrownDir);
			Chain->Transform()->SetRelativeRot(-XM_PI / 2.5f, 0.f, 0.f);
			Chain->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
			m_vecChain.push_back(Chain);
		}
	}
}

void CMagic_HookScript::tick()
{
	if (!m_bActive)
		return;

	PaveChain();

	Vec3 Diff = m_vStartPos - Transform()->GetWorldPos();
	Diff.y = 0.f;
	m_fDistancetoTarget = Diff.Length();

	if(!m_bSnatch)
	{
		m_fTime += DT;
		if (m_fTime > 0.5f)
		{
			if (abs(m_fDistancetoTarget) < 150.f)
			{
				m_pOwner->FailSnatch();
				Destroy();
			}
			if(!m_bReturn)
			{
				Rigidbody()->SetVelocity(-m_vThrownDir * 300000.f);
				m_bReturn = true;
			}
		}

	}

}

void CMagic_HookScript::Clear()
{
	m_vecChain = {};
	m_vStartPos = {};
	m_vThrownDir = {};
	m_fTime = 0.f;
	m_fDistancetoTarget = 0.f;
	m_fChainSpacing = 0.f;
	m_bSnatch = false;
	m_bReturn = false;

}

void CMagic_HookScript::Active(bool _bActive)
{
	m_bActive = _bActive;

	if(!m_bActive)
	{
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			m_vecChain[i]->Transform()->SetRelativeScale(Scale, Scale, Scale);
		}
	}
}

void CMagic_HookScript::BeginOverlap(CCollider3D* _Other)
{
	// 갈고리를 걸 수 있는 obj와 충돌했다면 hooking 상태로 전환
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER
		|| _Other->GetOwner()->GetLayerIndex() == (int)LAYER::ANCHOR)
	{
		if(!m_bReturn)
		{
			m_pOwner->Snatch(Transform()->GetWorldPos());
			m_bSnatch = true;
		}
	}
}

void CMagic_HookScript::EndOverlap(CCollider3D* _Other)
{
}

void CMagic_HookScript::SaveToLevelFile(FILE* _File)
{
}

void CMagic_HookScript::LoadFromLevelFile(FILE* _FILE)
{
}

void CMagic_HookScript::PaveChain()
{
	// 체인 1개보다 Hook이 멀리 나가면 Chain을 거리만큼 보이게 함.
	if (m_fDistancetoTarget >= m_fChainSpacing)
	{
		int ActiveChain = m_fDistancetoTarget / m_fChainSpacing;
		if (ActiveChain > 80)
			ActiveChain = 80;

		if (m_bReturn)
		{
			for (int j = 79; j >= ActiveChain; --j)
			{
				m_vecChain[j]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			}
		}
		else
		{
			for (int i = 0; i < ActiveChain; ++i)
			{
				m_vecChain[i]->Transform()->SetRelativeScale(Vec3(2.f, 2.f, 2.f));
			}
			for(int j = ActiveChain; j < 80; ++j)
			{
				m_vecChain[j]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			}
		}

	}
}
