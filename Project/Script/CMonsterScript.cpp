#include "pch.h"
#include "CMonsterScript.h"
#include "CStateScript.h"
#include "CTrace.h"



CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::begin()
{

	m_pState = GetOwner()->GetScript<CStateScript>();
	m_pState->AddState(L"Trace", new CTrace);
	m_pState->ChangeState(L"Trace");
}

void CMonsterScript::tick()
{
	if(KEY_TAP(KEY::SPACE))
	{
	}
}

void CMonsterScript::BeginOverlap(CCollider2D* _Other)
{
}

