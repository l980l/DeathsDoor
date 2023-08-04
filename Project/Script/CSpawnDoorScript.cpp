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
	// 등장 순간 한 바퀴 돌면서 Bloom효과를 주면서 몬스터를 스폰하고 FireBurn 효과를 주며 사라질 것
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
