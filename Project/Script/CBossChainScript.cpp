#include "pch.h"
#include "CBossChainScript.h"
#include "CCrowBossChainThrow.h"

CBossChainScript::CBossChainScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSCHAINSCRIPT)
	, m_pChainScript(nullptr)
	, m_vecChain{}
	, m_vThrowStartPos{}
	, m_vThrownDir{}
	, m_vThrownRot{}
	, m_fThrowDistance(0.f)
	, m_fDistancetoTarget(0.f)
	, m_fChainSpacing(0.f)
	, m_bActive(false)
{
}

CBossChainScript::~CBossChainScript()
{
}

void CBossChainScript::begin()
{
}

void CBossChainScript::tick()
{
	// 던지지 않았다면 return
	if (!m_bActive)
		return;

	Vec3 Diff = m_vThrowStartPos - Transform()->GetWorldPos();
	m_fDistancetoTarget = Diff.Length();

	Vec3 CurPos = Transform()->GetRelativePos();
	CurPos += m_vThrownDir * 2500.f * DT;
	Transform()->SetRelativePos(CurPos);

	// 돌아오는 도중에 시작지점과 가까이 왔다면 Hook 종료
	
	if (m_fDistancetoTarget >= m_fThrowDistance)
	{
		// 날아가야 하는 거리를 다 날아갔다면 Chain State에 날아가게 해야 함.
	}		
	
	// 시작지점과의 거리만큼 Chain을 활성화
	PaveChain();
}

void CBossChainScript::Active(bool _bActive)
{
	m_bActive = _bActive;
	if (m_bActive)
	{
		Transform()->SetRelativePos(m_vThrowStartPos);
		Transform()->SetRelativeScale(Vec3(0.7f));
		Collider3D()->SetOffsetScale(Vec3(100.f));
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			int a = i % 2;
			m_vecChain[i]->Transform()->SetRelativePos(m_vThrowStartPos + (m_vThrownDir * m_fChainSpacing * i));
			if (1 == a)
				m_vecChain[i]->Transform()->SetRelativeRot(Vec3(0.f, m_vThrownRot.y, XM_PI / 2.f));
			else
				m_vecChain[i]->Transform()->SetRelativeRot(Vec3(0.f, m_vThrownRot.y, 0.f));
		}
	}
	else
	{
		Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		Collider3D()->SetOffsetScale(Vec3(0.f));
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			m_vecChain[i]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		}
		Clear();
	}
}

void CBossChainScript::PaveChain()
{
	// 체인 1개보다 Hook이 멀리 나가면 Chain을 거리만큼 보이게 함.
	if (m_fDistancetoTarget >= m_fChainSpacing)
	{
		int ActiveChain = m_fDistancetoTarget / m_fChainSpacing;
		if (ActiveChain > 80)
			ActiveChain = 80;

		for (int i = 0; i < 80; ++i)
		{
			if (i < ActiveChain)
				m_vecChain[i]->Transform()->SetRelativeScale(Vec3(2.f, 2.f, 2.f));
			else
				m_vecChain[i]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
		}
	}
	else
	{
		for (int i = 0; i < 80; ++i)
		{
			m_vecChain[i]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
		}
	}
}

void CBossChainScript::Clear()
{
	m_vThrowStartPos = {};
	m_vThrownDir = {};
	m_vThrownRot = {};
	m_fThrowDistance = 0.f;
	m_fDistancetoTarget = 0.f;
	m_bActive = false;
}
