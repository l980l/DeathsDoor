#include "pch.h"
#include "CSpawnDoorScript.h"

CSpawnDoorScript::CSpawnDoorScript()
	: CScript((UINT)SCRIPT_TYPE::SPAWNDOORSCRIPT)
	, m_strSpawnMstName{}
	, m_fDelay(0.f)
	, m_bSpawn(false)
{
}

CSpawnDoorScript::~CSpawnDoorScript()
{
}

void CSpawnDoorScript::begin()
{
}

void CSpawnDoorScript::tick()
{
}
