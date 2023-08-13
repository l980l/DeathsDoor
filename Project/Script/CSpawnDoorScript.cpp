#include "pch.h"
#include "CSpawnDoorScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CSpawnMgr.h"
#include <Engine/CPhysXMgr.h>

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
	m_fDelay -= DT;
	if (m_fDelay <= 0.f && m_bSpawn == false)
	{
		CLevelSaveLoadInScript script;
		CGameObject* pMonster = script.SpawnandReturnPrefab(m_strSpawnMstName, (int)LAYER::MONSTER, Transform()->GetWorldPos());
		pMonster->Rigidbody()->SetRigidPos(Transform()->GetWorldPos());
		SetLifeSpan(1.5f);
		m_bSpawn = true;
		

	}
}
