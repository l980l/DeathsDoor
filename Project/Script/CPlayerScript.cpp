#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CStateScript.h"
#include "PlayerStates.h"

#include <Engine\CRenderMgr.h>

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_pState(nullptr)
{
}

CPlayerScript::~CPlayerScript()
{
	if (nullptr == m_pState)
		delete m_pState;
}

void CPlayerScript::begin()
{
	if(nullptr == m_pState)
	{
		m_pState = GetOwner()->GetScript<CStateScript>();
	}
	m_pState->AddState(L"Idle", new CPlyIdle);
	m_pState->AddState(L"Walk", new CPlyWalk);
	m_pState->AddState(L"Dodge", new CPlyDodge);
	m_pState->AddState(L"Fall", new CPlyFall);
	m_pState->AddState(L"Hit", new CPlyHit);
	m_pState->AddState(L"Dead", new CPlyDead);
	m_pState->AddState(L"Attack", new CPlyAttack);
	m_pState->AddState(L"Magic", new CPlyAttack_Magic);
	m_pState->ChangeState(L"Idle");
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{


}


void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	// 벽에 부딪힌다면 밀어내기
	if ((int)LAYER::WALL == _Other->GetOwner()->GetLayerIndex())
	{

	}

	// 아래는 공격 관련으로 무적이라면 return;
	if (m_bInvincible)
		return;

	if ((int)LAYER::MONSTERPROJECTILE == _Other->GetOwner()->GetLayerIndex())
	{
		m_pState->ChangeState(L"Hit");
		Stat CurStat = m_pState->GetStat();
		CurStat.HP -= 1;
		m_pState->SetStat(CurStat);
		if (CurStat.HP <= 0)
			m_pState->ChangeState(L"Dead");
		else
			m_pState->ChangeState(L"Hit");
	}
}


void CPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
}