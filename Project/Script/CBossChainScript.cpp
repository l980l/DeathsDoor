#include "pch.h"
#include "CBossChainScript.h"
#include "CCrowBossSlidingReady.h"
#include "CCrowBossSliding.h"

CBossChainScript::CBossChainScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSCHAINSCRIPT)
	, m_pChainScript(nullptr)
	, m_pSlidingScript(nullptr)
	, m_vecChain{}
	, m_vThrowStartPos{}
	, m_vThrownDir{}
	, m_vThrownRot{}
	, m_fThrowDistance(0.f)
	, m_fDistancetoTarget(0.f)
	, m_fChainSpacing(50.f)
	, m_fDelay(0.f)
	, m_bActive(false)
	, m_bRetrieve(false)
	, m_bMulti(false)
	, m_iActiveCount(0)
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
	for (size_t i = 0; i < m_vecChain.size(); ++i)
	{
		m_vecChain[i]->GetRenderComponent()->GetMaterial(0)->SetScalarParam(INT_1, &a);
		m_vecChain[i]->GetRenderComponent()->GetMaterial(0)->SetScalarParam(VEC4_0, &Color);
	}
}

void CBossChainScript::tick()
{
	// ������ �ʾҴٸ� return
	if (!m_bActive)
		return;
	if (m_fDelay >= 0.f)
	{
		m_fDelay -= DT;
		return;
	}

	Vec3 vCurPos = Transform()->GetRelativePos();
	Vec3 vDiff = m_vThrowStartPos - vCurPos;
	vDiff.y = 0.f;
	m_fDistancetoTarget = vDiff.Length();

	PaveChain();

	// ȸ�� �ÿ��� �Ÿ��� ���� �罽 ������ �ϰ� ��.
	if (m_bRetrieve)
		return;

	// ���ƿ��� ���߿� ���������� ������ �Դٸ� Hook ����	
	if (m_fDistancetoTarget >= m_fThrowDistance)
	{
		if (m_bMulti)
			m_pSlidingScript->AddTargetPos(GetOwner()->Transform()->GetWorldPos(), m_vThrowStartPos);
		else
			m_pSlidingScript->AddTargetPos(GetOwner()->Transform()->GetWorldPos());
		m_pChainScript->HookArrive();
		m_bActive = false;
	}		
	else	
	{
		Vec3 CurPos = Transform()->GetRelativePos();
		CurPos += m_vThrownDir * 4000.f * DT;
		Transform()->SetRelativePos(CurPos);
		// ������������ �Ÿ���ŭ Chain�� Ȱ��ȭ
	}

}

void CBossChainScript::Active(bool _bActive, bool _bMulti, float _fDelay = 0)
{
	m_bActive = _bActive;
	if (m_bActive)
	{
		Transform()->SetRelativePos(m_vThrowStartPos);
		Transform()->SetRelativeRot(Vec3(XM_PI * 0.5f, m_vThrownRot.y, 0.f));
		Transform()->SetRelativeScale(Vec3(1.2f));
		Collider3D()->SetOffsetScale(Vec3(100.f));
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			m_vecChain[i]->Transform()->SetRelativePos(m_vThrowStartPos + (m_vThrownDir * m_fChainSpacing * i));
			m_vecChain[i]->Transform()->SetRelativeRot(Vec3(XM_PI, m_vThrownRot.y + XM_PI / 2.f, 0.f));
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
	// ü�� 1������ Hook�� �ָ� ������ Chain�� �Ÿ���ŭ ���̰� ��.
	if(!m_bRetrieve)
	{
		if (m_fDistancetoTarget >= m_fChainSpacing)
		{
			int m_iActiveCount = m_fDistancetoTarget / m_fChainSpacing;
			if (m_iActiveCount > ChainCount)
				m_iActiveCount = ChainCount;

			for (int i = 0; i < ChainCount; ++i)
			{
				if (i < m_iActiveCount)
					m_vecChain[i]->Transform()->SetRelativeScale(Vec3(5.f, 5.f, 5.f));
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
	else
	{
		int ActiveCount = ChainCount - m_fDistancetoTarget / m_fChainSpacing;
		if (m_iActiveCount < 0)
			m_iActiveCount = 0;
		for (int i = ActiveCount;  i >= m_iActiveCount; --i)
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
