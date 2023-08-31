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

void CGhostHit::Enter()
{
	Vec3 vPlayerPos = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetWorldPos();
	vDir = vPlayerPos - GetOwner()->Transform()->GetWorldPos();
	vDir.y = 0;
	vDir.Normalize();
}

void CGhostHit::tick()
{
	GetOwner()->Rigidbody()->SetVelocity(-vDir * 600.f);
}

void CGhostHit::Exit()
{
	
}
