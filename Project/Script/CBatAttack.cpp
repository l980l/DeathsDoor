#include "pch.h"
#include "CBatAttack.h"
#include "CLevelSaveLoadInScript.h"

CBatAttack::CBatAttack()	:
	m_fTime(0.f)
{
}

CBatAttack::~CBatAttack()
{
}

void CBatAttack::tick()
{
	m_fTime += DT;
	if (m_fTime >= 1.f)
	{
		ChangeState(L"BatIdle");
		m_fTime = 0.f;
	}
	m_fTime;
}

void CBatAttack::Enter()
{
	GetOwner()->Animator3D()->Play(2, false); 
	CLevelSaveLoadInScript::SpawnPrefab(L"prefab\\BatAttack.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CBatAttack::Exit()
{
	
}
