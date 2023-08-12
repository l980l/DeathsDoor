#include "pch.h"
#include "CGhostScript.h"
#include "CTrace.h"
#include "CStateScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CPlyAttack.h"
#include "CGhostHit.h"
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
		m_pStateScript->AddState(L"GhostHit", new CGhostHit);
		
		m_pStateScript->ChangeState(L"Trace");
	}


	GetOwner()->Rigidbody()->SetVelocityLimit(300.f);

	// 초기 스탯 설정.
	m_stat.Attack = 1;
	m_stat.Speed = 300;
	m_pStateScript->SetStat(m_stat);

	SetLifeSpan(10.f);
}

void CGhostScript::tick()
{

}

Vec3 CGhostScript::GetDir(Vec3 _start, Vec3 _target)
{
	// 아래축을 기준으로 CurPos에서 TargetPos를 바라보는 angle 반환
	Vec3 CurPos = _start;
	Vec2 vDefault = Vec2(0.f, -1.f);
	Vec3 TargetPos = _target;
	Vec3 vDir = TargetPos - CurPos;
	vDir.y = 0;
	vDir.Normalize();

	return vDir;
}

void CGhostScript::BeginOverlap(CCollider3D* _Other)
{
	CLevelSaveLoadInScript script;
	if (L"Slash_R" == _Other->GetOwner()->GetName()|| L"Slash_L" == _Other->GetOwner()->GetName() && isHit == false)
	{
		//player가 바라 보는 방향으로 이동
		isHit = true;
		m_pStateScript->ChangeState(L"GhostHit");
	}
	if (L"Player" == _Other->GetOwner()->GetName() && isHit ==false)
	{
		//player damage & dead

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
