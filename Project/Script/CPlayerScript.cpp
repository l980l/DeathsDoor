#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CStateScript.h"
#include "PlayerStates.h"
#include "CPlayerWeaponScript.h"

#include <Engine\CRenderMgr.h>

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_pStateScript(nullptr)
	, m_iCurMagic(0)
	, m_bInvincible(false)
	, m_pSword(nullptr)
{
}

CPlayerScript::~CPlayerScript()
{
	if (nullptr == m_pStateScript)
		delete m_pStateScript;
}

void CPlayerScript::begin()
{
	/*if (nullptr == m_pSword)
	{
		m_pSword = GetOwner()->GetChild()[0]->GetScript<CPlayerWeaponScript>();
	}*/
	if(nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>(); 
		m_pStateScript->AddState(L"Idle", new CPlyIdle);
		m_pStateScript->AddState(L"Walk", new CPlyWalk);
		m_pStateScript->AddState(L"Run", new CPlyRun);
		m_pStateScript->AddState(L"Dodge", new CPlyDodge);
		m_pStateScript->AddState(L"Fall", new CPlyFall);
		m_pStateScript->AddState(L"Hit", new CPlyHit);
		m_pStateScript->AddState(L"Dead", new CPlyDead);
		m_pStateScript->AddState(L"Attack", new CPlyAttack);
		m_pStateScript->AddState(L"Ladder", new CPlyLadder);
		m_pStateScript->AddState(L"Arrow", new CPlyMagic_Arrow);
		m_pStateScript->AddState(L"Fire", new CPlyMagic_Fire);
		m_pStateScript->AddState(L"Bomb", new CPlyMagic_Bomb);
		m_pStateScript->AddState(L"Hook", new CPlyMagic_Hook);
		m_pStateScript->AddState(L"Hooking", new CPlyMagic_Hooking);
		m_pStateScript->ChangeState(L"Idle");
		MeshRender()->GetDynamicMaterial(0);
	}	
}

void CPlayerScript::tick()
{
	SetMagicType();
}

void CPlayerScript::BeginOverlap(CCollider3D* _Other)
{
	// 벽에 부딪힌다면 밀어내기
	if ((int)LAYER::GROUND == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(true);
	}

	// 아래는 공격 관련으로 무적이라면 return;
	if (m_bInvincible)
		return;

	if ((int)LAYER::MONSTERPROJECTILE == _Other->GetOwner()->GetLayerIndex())
	{
		ChangeState(L"Hit");
		Stat CurStat = m_pStateScript->GetStat();
		CurStat.HP -= 1;
		m_pStateScript->SetStat(CurStat);
		if (CurStat.HP <= 0)
		{
			ChangeState(L"Dead");
		}
		else
		{
			ChangeState(L"Hit");
		}
	}
}

void CPlayerScript::EndOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::GROUND == _Other->GetOwner()->GetLayerIndex())
	{
		Rigidbody()->SetGround(false);
	}
}

void CPlayerScript::ChangeState(wstring _strStateName)
{
	m_pStateScript->ChangeState(_strStateName);
	m_pSword->ChangeState(_strStateName);
}

void CPlayerScript::SetMagicType()
{
	if (KEY_TAP(KEY::_1))
		m_iCurMagic = (UINT)PLAYER_MAGIC::ARROW;
	if (KEY_TAP(KEY::_2))
		m_iCurMagic = (UINT)PLAYER_MAGIC::FIRE;
	if (KEY_TAP(KEY::_3))
		m_iCurMagic = (UINT)PLAYER_MAGIC::BOMB;
	if (KEY_TAP(KEY::_4))
		m_iCurMagic = (UINT)PLAYER_MAGIC::HOOK;
}

void CPlayerScript::ChangeMagicState()
{
	switch (PLAYER_MAGIC(m_iCurMagic))
	{
	case PLAYER_MAGIC::ARROW:
		ChangeState(L"Arrow");
		break;
	case PLAYER_MAGIC::FIRE:
		ChangeState(L"Fire");
		break;
	case PLAYER_MAGIC::BOMB:
		ChangeState(L"Bomb");
		break;
	case PLAYER_MAGIC::HOOK:
		ChangeState(L"Hook");
		break;
	}
}

void CPlayerScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
}