#include "pch.h"
#include "CGhostHit.h"
#include "CPlayerScript.h"
#include "CLevelSaveLoadInScript.h"

CGhostHit::CGhostHit()
{
}

CGhostHit::~CGhostHit()
{
}

void CGhostHit::tick()
{
	GetOwner()->Rigidbody()->SetVelocity(-Dir * 600.f);
}

void CGhostHit::Enter()
{
	playerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
	Dir = playerPos - GetOwner()->Transform()->GetWorldPos();
	Dir.y = 0;
	Dir.Normalize();
}

void CGhostHit::Exit()
{
	
}

void CGhostHit::BeginOverlap(CCollider2D* _Other)
{
	
}

void CGhostHit::OnOverlap(CCollider2D* _Other)
{
}

void CGhostHit::EndOverlap(CCollider2D* _Other)
{
}
