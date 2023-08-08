#include "pch.h"
#include "CGhostScript.h"
#include "CTrace.h"
#include "CStateScript.h"

CGhostScript::CGhostScript()		:
	CMonsterScript((UINT)SCRIPT_TYPE::GHOSTSCRIPT)
{
}

CGhostScript::CGhostScript(const CGhostScript& _Other)	:
	CMonsterScript((UINT)SCRIPT_TYPE::GHOSTSCRIPT)
{
}

CGhostScript::~CGhostScript()
{
}

void CGhostScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"Trace", new CTrace);
		
		m_pStateScript->ChangeState(L"Trace");
	}

	GetOwner()->Rigidbody()->SetVelocityLimit(300.f);

	// 초기 스탯 설정.
	m_stat.Speed = 300;
	m_pStateScript->SetStat(m_stat);

	SetLifeSpan(5.f);
}

void CGhostScript::tick()
{
}

void CGhostScript::BeginOverlap(CCollider3D* _Other)
{
	if (L"Sword" == _Other->GetOwner()->GetName())
	{
		//player가 바라 보는 방향으로 이동
	}
}

void CGhostScript::OnOverlap(CCollider3D* _Other)
{
}

void CGhostScript::EndOverlap(CCollider3D* _Other)
{
}

void CGhostScript::SaveToLevelFile(FILE* _File)
{
}

void CGhostScript::LoadFromLevelFile(FILE* _File)
{
}
