#include "pch.h"
#include "CBatAttack.h"
#include "CLevelSaveLoadInScript.h"

CBatAttack::CBatAttack()	:
	m_time(0.f)
{
}

CBatAttack::~CBatAttack()
{
}

void CBatAttack::tick()
{
	m_time += DT;
	if (m_time >= 1.f)
	{
		ChangeState(L"BatIdle");
		m_time = 0.f;
	}
	m_time;
}

void CBatAttack::Enter()
{
	GetOwner()->Animator3D()->Play(2, false); 
	CLevelSaveLoadInScript slscript;
	slscript.SpawnPrefab(L"prefab\\BatAttack.prefab", 3, GetOwner()->Transform()->GetWorldPos(), 0.2f);
}

void CBatAttack::Exit()
{
	
}

void CBatAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CBatAttack::OnOverlap(CCollider2D* _Other)
{
}

void CBatAttack::EndOverlap(CCollider2D* _Other)
{
}
