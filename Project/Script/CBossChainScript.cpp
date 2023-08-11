#include "pch.h"
#include "CBossChainScript.h"
#include "CCrowBossSlidingReady.h"
#include "CCrowBossSliding.h"

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
	int a = 1;
	Vec4 Color = Vec4(0.f, 0.f, 0.f, 1.f);
	GetOwner()->GetRenderComponent()->GetMaterial(0)->SetScalarParam(INT_1, &a);
	GetOwner()->GetRenderComponent()->GetMaterial(0)->SetScalarParam(VEC4_0, &Color);

}

void CBossChainScript::tick()
{
	// 던지지 않았다면 return
	if (!m_bActive)
		return;
	if (m_fDelay > 0.f)
	{
		m_fDelay -= DT;
		return;
	}
	Vec3 Diff = m_vThrowStartPos - Transform()->GetWorldPos();
	m_fDistancetoTarget = Diff.Length();


	// 돌아오는 도중에 시작지점과 가까이 왔다면 Hook 종료
	
	if (m_fDistancetoTarget >= m_fThrowDistance)
	{
		m_pSlidingScript->AddTargetPos(GetOwner()->Transform()->GetWorldPos());
		m_pChainScript->HookArrive();
	}		
	else	
	{
		Vec3 CurPos = Transform()->GetRelativePos();
		CurPos += m_vThrownDir * 1500.f * DT;
		Transform()->SetRelativePos(CurPos);

		// 시작지점과의 거리만큼 Chain을 활성화
		PaveChain();
	}
}

void CBossChainScript::Active(bool _bActive, float _fDelay = 0)
{
	m_bActive = _bActive;
	if (m_bActive)
	{
		Transform()->SetRelativePos(m_vThrowStartPos);
		Transform()->SetRelativeScale(Vec3(0.7f));
		Collider3D()->SetOffsetScale(Vec3(100.f));
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			m_vecChain[i]->Transform()->SetRelativePos(m_vThrowStartPos + (m_vThrownDir * m_fChainSpacing * i));
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
	m_fDelay = _fDelay;
}

void CBossChainScript::PaveChain()
{
	int ChainCount = (int)m_vecChain.size();
	// 체인 1개보다 Hook이 멀리 나가면 Chain을 거리만큼 보이게 함.
	if (m_fDistancetoTarget >= m_fChainSpacing)
	{
		int ActiveChain = m_fDistancetoTarget / m_fChainSpacing;
		if (ActiveChain > ChainCount)
			ActiveChain = ChainCount;

		for (int i = 0; i < ChainCount; ++i)
		{
			if (i < ActiveChain)
				m_vecChain[i]->Transform()->SetRelativeScale(Vec3(2.f, 2.f, 2.f));
			else
				m_vecChain[i]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
		}
	}
	else
	{
		for (int i = 0; i < ChainCount; ++i)
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
