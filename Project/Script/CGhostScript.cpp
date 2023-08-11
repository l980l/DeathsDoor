#include "pch.h"
#include "CGhostScript.h"
#include "CTrace.h"
#include "CStateScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CPhysXMgr.h>

CGhostScript::CGhostScript()		:
	CMonsterScript((UINT)SCRIPT_TYPE::GHOSTSCRIPT),
	isHit(false)
{
}

CGhostScript::CGhostScript(const CGhostScript& _Other)	:
	CMonsterScript((UINT)SCRIPT_TYPE::GHOSTSCRIPT),
	isHit(false)
{
}

CGhostScript::~CGhostScript()
{
}

void CGhostScript::begin()
{
	// ���� ���� ����.
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


	GetOwner()->Rigidbody()->SetVelocityLimit(100.f);

	// �ʱ� ���� ����.
	m_stat.Attack = 1;
	m_stat.Speed = 300;
	m_pStateScript->SetStat(m_stat);

	SetLifeSpan(5.f);
}

void CGhostScript::tick()
{
}

void CGhostScript::BeginOverlap(CCollider3D* _Other)
{
	CLevelSaveLoadInScript script;
	if (L"Sword" == _Other->GetOwner()->GetName())
	{
		//player�� �ٶ� ���� �������� �̵�
		isHit = true;
	}
	if (L"Player" == _Other->GetOwner()->GetName() && isHit ==false)
	{
		//player damage & dead

		//script.SpawnPrefab(L"prefab\\")
		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		//CPhysXMgr::GetInst()->ReleaseDynamic()
		GetOwner()->SetLifeSpan(0.f);
	}
	if (L"GrimKnight" == _Other->GetOwner()->GetName() && isHit == true)
	{
		//player damage & dead
		Stat grimStatus = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		grimStatus.HP -= 10;
		//script.SpawnPrefab(L"prefab\\")
		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
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
