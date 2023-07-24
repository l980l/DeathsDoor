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
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"BatIdle");
	}
}

void CBatAttack::Enter()
{
	GetOwner()->Animator3D()->Play(2, false);
	CLevelSaveLoadInScript slscript;
	slscript.SpawnPrefab(L"prefab\\BatAttackRange.prefab", 3, GetOwner()->Transform()->GetWorldPos(), 0.2f);
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
