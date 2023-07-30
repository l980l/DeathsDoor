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
	, m_fChainSpacing(15.f)
	, m_bSnatch(false)
	, m_bReturn(false)
	, m_bActive(false)
{	
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

void CMagic_HookScript::Clear()
{
	m_vStartPos = {};
	m_vThrownDir = {};
	m_fTime = 0.f;
	m_fDistancetoTarget = 0.f;
	m_bSnatch = false;
	m_bReturn = false;
	m_bActive = false;
}

void CMagic_HookScript::begin()
{
}

void CMagic_HookScript::tick()
{
	// 던지지 않았다면 return
	if (!m_bActive)
		return;

	// 시작지점과의 거리만큼 Chain을 활성화
	PaveChain();

	Vec3 Diff = m_vStartPos - Transform()->GetWorldPos();
	m_fDistancetoTarget = Diff.Length();

	if(!m_bSnatch)
	{
		// 일정시간 이상 갔다면 돌아오도록 함.
		m_fTime += DT;
		// 시간이 지나고 첫 tick이라면 날아오던 반대편으로 방향을 바꿈
		
		if(m_bReturn)
		{
			// 돌아오는 도중에 시작지점과 가까이 왔다면 Hook 종료
			if (abs(m_fDistancetoTarget) < 100.f && m_bReturn)
			{
				Active(false);
				m_pOwner->FailSnatch();
			}
		}
		else
		{
			if (m_fTime > 0.5f)
			{
				m_bReturn = true;
				Rigidbody()->SetVelocity(-m_vThrownDir * 300000.f);
			}
		}

	}
}

void CMagic_HookScript::Active(bool _bActive)
{
	m_bActive = _bActive;
	m_fTime = 0.f;
	if(m_bActive)
	{
		Transform()->SetRelativeScale(1.f, 1.f, 1.f);
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			m_vecChain[i]->Transform()->SetRelativePos(m_vStartPos + (m_vThrownDir * m_fChainSpacing * i));
		}
	}
	else if(!m_bActive)
	{
		Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			m_vecChain[i]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		}
		Clear();
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
			Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
			m_pOwner->Snatch(Transform()->GetWorldPos());
			m_bSnatch = true;
		}
	}
}

void CMagic_HookScript::EndOverlap(CCollider3D* _Other)
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
				m_vecChain[i]->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			}
			for(int j = ActiveChain; j < 80; ++j)
			{
				m_vecChain[j]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			}
		}

	}
}
