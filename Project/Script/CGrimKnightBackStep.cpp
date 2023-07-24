#include "pch.h"
#include "CGrimKnightBackStep.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

void CGrimKnightBackStep::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"BackStep2");
	}
}

void CGrimKnightBackStep::Enter()
{
	//Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(9, false);

	//플레이어 반대 방향으로 이동
	CGameObject* player = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	Vec3 playerPos = player->Transform()->GetWorldPos();
	Vec3 dir = (GetOwner()->Transform()->GetWorldPos() - playerPos).Normalize();
	GetOwner()->Rigidbody()->AddVelocity(dir * 150);
}

void CGrimKnightBackStep::Exit()
{
}

void CGrimKnightBackStep::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightBackStep::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightBackStep::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightBackStep::CGrimKnightBackStep()
{
}

CGrimKnightBackStep::~CGrimKnightBackStep()
{
}
