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
}

void CMagic_HookScript::Clear()
{
	m_vStartPos = {};
	m_vThrownDir = {};
	m_vAttackDir = {};
	m_fTime = 0.f;
	m_fDistancetoTarget = 0.f;
	m_bSnatch = false;
	m_bReturn = false;
	m_bActive = false;
}

void CMagic_HookScript::begin()
{
	int a = 1;
	Vec4 Color = Vec4(0.2f, 0.5f, 0.2f, 1.f);
	MeshRender()->GetMaterial(0)->SetScalarParam(INT_1, &a);
	MeshRender()->GetMaterial(0)->SetScalarParam(VEC4_0, &Color);
	Vec4 ChainColor = Vec4(0.6f, 1.f, 0.6f, 1.f);
	for (size_t i = 0; i < m_vecChain.size(); ++i)
	{
		m_vecChain[i]->GetRenderComponent()->GetMaterial(0)->SetScalarParam(INT_1, &a);
		m_vecChain[i]->GetRenderComponent()->GetMaterial(0)->SetScalarParam(VEC4_0, &ChainColor);
	}
	Active(m_bActive);
}

void CMagic_HookScript::tick()
{
	// ������ �ʾҴٸ� return
	if (!m_bActive)
		return;

	Vec3 Diff = m_vStartPos - Transform()->GetWorldPos();
	m_fDistancetoTarget = Diff.Length();

	
	if(!m_bSnatch)
	{
		Vec3 CurPos = Transform()->GetRelativePos();
		CurPos += m_vThrownDir * 2500.f * DT;
		Transform()->SetRelativePos(CurPos);

		// �����ð� �̻� ���ٸ� ���ƿ����� ��.
		m_fTime += DT;

		// �ð��� ������ ù tick�̶�� ���ƿ��� �ݴ������� ������ �ٲ�		
		if(m_bReturn)
		{
			// ���ƿ��� ���߿� ���������� ������ �Դٸ� Hook ����
			if (abs(m_fDistancetoTarget) < 100.f)
			{
				Active(false);
				m_pOwner->FailSnatch();
			}
		}
		else
		{
			if (m_fTime > 0.4f)
			{
				m_bReturn = true;
				m_vThrownDir *= -1.f;
			}
		}
	}

	// ������������ �Ÿ���ŭ Chain�� Ȱ��ȭ
	PaveChain();
}

// Player�� Hook�� ������ ���� �Ǵ� �����⸦ �����ߴٸ� Ȱ��/��Ȱ��ȭ
void CMagic_HookScript::Active(bool _bActive)
{
	m_bActive = _bActive;
	m_fTime = 0.f;
	if(m_bActive)
	{
		Transform()->SetRelativePos(m_vStartPos);
		Transform()->SetRelativeScale(Vec3(0.7f));
		Collider3D()->SetOffsetScale(Vec3(100.f));
		for (size_t i = 0; i < m_vecChain.size(); ++i)
		{
			int a = i % 2;
			m_vecChain[i]->Transform()->SetRelativePos(m_vStartPos + (m_vThrownDir * m_fChainSpacing * i));
			if(1 == a)
				m_vecChain[i]->Transform()->SetRelativeRot(Vec3(XMConvertToRadians(-33.f) + m_vAttackDir.y, XM_PIDIV2, 0.f));
			else
				m_vecChain[i]->Transform()->SetRelativeRot(Vec3(XMConvertToRadians(-33.f), m_vAttackDir.y, 0.f));
		}
	}
	else if(!m_bActive)
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

void CMagic_HookScript::BeginOverlap(CCollider3D* _Other)
{
	// ������ �� �� �ִ� obj�� �浹�ߴٸ� hooking ���·� ��ȯ
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

void CMagic_HookScript::PaveChain()
{
	// ü�� 1������ Hook�� �ָ� ������ Chain�� �Ÿ���ŭ ���̰� ��.
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
			for (int i = 0; i < 80; ++i)
			{
				if(i < ActiveChain)
					m_vecChain[i]->Transform()->SetRelativeScale(Vec3(2.f, 2.f, 2.f));
				else
					m_vecChain[i]->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			}
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
