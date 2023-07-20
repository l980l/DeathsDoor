#include "pch.h"
#include "CMonsterScript.h"
#include "CStateScript.h"
#include "CBatScript.h"
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

	CBatScript* pBatScript = GetOwner()->GetScript<CBatScript>();

	m_pStateScript = GetOwner()->GetScript<CStateScript>();
	m_pStateScript->AddState(L"Trace", new CTrace);
	m_pStateScript->ChangeState(L"Trace");
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

