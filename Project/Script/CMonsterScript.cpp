#include "pch.h"
#include "CMonsterScript.h"
#include "CStateScript.h"


CMonsterScript::CMonsterScript(UINT SCRIPT_TYPE) :
	CScript(SCRIPT_TYPE)
	, m_pStateScript(nullptr)
	, m_pPlayer(nullptr)
	, m_bDetect(false)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::begin()
{
	// �÷��̾� ����.
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	}

	// Crack Texture ���ε�.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		Ptr<CTexture> CrackTextue = CResMgr::GetInst()->Load<CTexture>(L"texture\\MonsterCrack.png", L"texture\\MonsterCrack.png");
		Ptr<CMaterial> mtrl = MeshRender()->GetSharedMaterial(i);
		mtrl->SetTexParam(TEX_7, CrackTextue.Get());		// �ϴ� 7������ ��������.
	}
}

void CMonsterScript::tick()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		Ptr<CMaterial> mtrl = MeshRender()->GetSharedMaterial(i);
		float HPRatio = (float)m_pStateScript->GetStat().HP / (float)m_pStateScript->GetStat().Max_HP;
		mtrl->SetScalarParam(FLOAT_0, &HPRatio);
	}
}

void CMonsterScript::BeginOverlap(CCollider3D* _Other)
{
}

void CMonsterScript::OnOverlap(CCollider3D* _Other)
{
}

void CMonsterScript::EndOverlap(CCollider3D* _Other)
{
}

