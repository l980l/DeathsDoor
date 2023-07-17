#include "pch.h"
#include "CMonsterScript.h"


CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
}

CMonsterScript::~CMonsterScript()
{
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

