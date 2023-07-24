#include "pch.h"
#include "CKnightJumpAttack.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CGameObject.h>

void CKnightJumpAttack::tick()
{
	//playerPos·Î ÀÌµ¿
	CGameObject* player = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	Vec3 playerPos = player->Transform()->GetWorldPos();
	Vec3 dir = (playerPos - GetOwner()->Transform()->GetWorldPos()).Normalize();
	float distance = GetDistance(playerPos, GetOwner()->Transform()->GetWorldPos());
	GetOwner()->Rigidbody()->AddVelocity(dir * distance);

	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"JumpAttack2");
	}
}

void CKnightJumpAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(7, false);
}

void CKnightJumpAttack::Exit()
{
}

void CKnightJumpAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack::OnOverlap(CCollider2D* _Other)
{
}

void CKnightJumpAttack::EndOverlap(CCollider2D* _Other)
{
}

CKnightJumpAttack::CKnightJumpAttack()
{
}

CKnightJumpAttack::~CKnightJumpAttack()
{
}
