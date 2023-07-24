#include "pch.h"
#include "CGrimKnightSpinDown.h"

void CGrimKnightSpinDown::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"SpinUp");
	}
}

void CGrimKnightSpinDown::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(1, false);

	//공격 prefab 생성
	//CLevelSaveLoadInScript script;
	//script.SpawnPrefab(L"SpinDown", 5, GetOwner()->Transform()->GetWorldPos(), 0.2f);

}

void CGrimKnightSpinDown::Exit()
{
}

void CGrimKnightSpinDown::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightSpinDown::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightSpinDown::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightSpinDown::CGrimKnightSpinDown()
{
}

CGrimKnightSpinDown::~CGrimKnightSpinDown()
{
}
