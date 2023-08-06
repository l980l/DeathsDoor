#include "pch.h"
#include "CMonsterScript.h"
#include "CStateScript.h"


CMonsterScript::CMonsterScript(UINT SCRIPT_TYPE) :
	CScript(SCRIPT_TYPE)
	, m_pStateScript(nullptr)
	, m_pPlayer(nullptr)
	, m_bDetect(false)
	, m_bPaperBurnEffect(false)
	, m_bSendDeadTime(false)
	, m_fLastHitTime(-3.f)
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
		// 7������ ������. CrackTexture.
		Ptr<CTexture> CrackTextue = CResMgr::GetInst()->Load<CTexture>(L"texture\\Deaths_Door\\MonsterCrack.png", L"texture\\Deaths_Door\\MonsterCrack.png");
		Ptr<CMaterial> mtrl = MeshRender()->GetSharedMaterial(i);
		mtrl->SetTexParam(TEX_7, CrackTextue.Get());		

		// 6������ ������. Paperburn�� noise texture.
		Ptr<CTexture> NoiseTextue = CResMgr::GetInst()->Load<CTexture>(L"texture\\Deaths_Door\\noise.png", L"texture\\Deaths_Door\\noise.png");
		mtrl->SetTexParam(TEX_6, NoiseTextue.Get());
	}
}

void CMonsterScript::tick()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		Ptr<CMaterial> mtrl = MeshRender()->GetSharedMaterial(i);
		
		// ���� ü�� ���� ������. FLOAT_0�� ����.
		float HPRatio = (float)m_pStateScript->GetStat().HP / (float)m_pStateScript->GetStat().Max_HP;
		mtrl->SetScalarParam(FLOAT_0, &HPRatio);

		// Paperburn ȿ���� �ֱ� ������ ��, ������� �帥 �ð� ������. FLOAT_1�� ����. �ѹ��� ������ �ؼ� m_bSendDeadTime�� �����. 
		if (m_bPaperBurnEffect && !m_bSendDeadTime)
		{
			mtrl->SetScalarParam(FLOAT_1, &GlobalData.tAccTime);
			m_bSendDeadTime = true;
		}

		// �ǰ� ����Ʈ
		float fHitAfterTime = GlobalData.tAccTime - m_fLastHitTime;		// �ǰ� ���� ���� �ð�.
		int HitEffect = 0;

		if (fHitAfterTime < 0.2f)
			HitEffect = 1;

		mtrl->SetScalarParam(INT_3, &HitEffect);
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

