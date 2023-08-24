#include "pch.h"
#include "CSpawnDoorScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CSpawnMgr.h"
#include <Engine/CPhysXMgr.h>
#include "CMonsterScript.h"

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
	if (m_bSpawn)
		return;

	if (m_fDelay > 0.f)
		m_fDelay -= DT;
	else if(m_fDelay <= 0.f)
	{
		CGameObject* pMonster = CLevelSaveLoadInScript::SpawnandReturnPrefab(m_strSpawnMstName, (int)LAYER::MONSTER, GetOwner()->Transform()->GetWorldPos());
		pMonster->Rigidbody()->SetRigidPos(Transform()->GetWorldPos()); //rigidbody global pos setup
		pMonster->GetScript<CMonsterScript>()->SpawnByDoor();

		// 페이퍼번을 주고 사라질 것
		SetLifeSpan(1.5f);
		m_bSpawn = true;
	}
}
