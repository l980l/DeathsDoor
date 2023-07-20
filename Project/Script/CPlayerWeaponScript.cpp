#include "pch.h"
#include "CPlayerWeaponScript.h"
#include "CStateScript.h"

CPlayerWeaponScript::CPlayerWeaponScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERWEAPONSCRIPT)
{
}

CPlayerWeaponScript::~CPlayerWeaponScript()
{
}

void CPlayerWeaponScript::begin()
{
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
	}
	//m_pStateScript->AddState(L"Idle", new CPlyIdle);
	//m_pStateScript->AddState(L"Walk", new CPlyWalk);
	//m_pStateScript->AddState(L"Dodge", new CPlyDodge);
	//m_pStateScript->AddState(L"Fall", new CPlyFall);
	//m_pStateScript->AddState(L"Hit", new CPlyHit);
	//m_pStateScript->AddState(L"Dead", new CPlyDead);
	//m_pStateScript->AddState(L"Attack", new CPlyAttack);
	//m_pStateScript->AddState(L"Magic", new CPlyAttack_Magic);
	//m_pStateScript->ChangeState(L"Idle");
	//MeshRender()->GetDynamicMaterial(0);
}

void CPlayerWeaponScript::tick()
{
}

void CPlayerWeaponScript::BeginOverlap(CCollider3D* _Other)
{
}

void CPlayerWeaponScript::EndOverlap(CCollider3D* _Other)
{
}

void CPlayerWeaponScript::ChangeState(wstring _strStateName)
{
	m_pStateScript->ChangeState(_strStateName);
}

void CPlayerWeaponScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerWeaponScript::LoadFromLevelFile(FILE* _FILE)
{
}
