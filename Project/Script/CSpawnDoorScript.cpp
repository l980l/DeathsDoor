#include "pch.h"
#include "CSpawnDoorScript.h"
#include "CLevelSaveLoadInScript.h"

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
	// ���� ���� �� ���� ���鼭 Bloomȿ���� �ָ鼭 ���͸� �����ϰ� FireBurn ȿ���� �ָ� ����� ��
}

void CSpawnDoorScript::tick()
{
	m_fDelay -= DT;
	if (m_fDelay <= 0.f)
	{
		CLevelSaveLoadInScript script;
		script.SpawnPrefab(m_strSpawnMstName, (int)LAYER::MONSTER, Transform()->GetWorldPos());
		SetLifeSpan(1.5f);
	}
}
