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
	GetOwner()->Rigidbody()->SetVelocity(-Dir * 400.f);
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
	CLevelSaveLoadInScript script;

	if (L"GrimKnight" == _Other->GetOwner()->GetName())
	{
		//player damage & dead
		Stat status = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		status.HP -= 10;
		//script.SpawnPrefab(L"prefab\\")
		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
	}
	if (L"Bat" == _Other->GetOwner()->GetName())
	{
		//player damage & dead
		Stat status = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		status.HP -= 10;

		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
	}
	if (L"Bazooka" == _Other->GetOwner()->GetName())
	{
		//player damage & dead
		Stat status = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		status.HP -= 10;

		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
	}
	if (L"Grunt" == _Other->GetOwner()->GetName())
	{
		//player damage & dead
		Stat status = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		status.HP -= 10;

		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
	}
	if (L"Knight" == _Other->GetOwner()->GetName())
	{
		//player damage & dead
		Stat status = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		status.HP -= 10;

		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
	}
	if (L"CrowBoss" == _Other->GetOwner()->GetName())
	{
		//player damage & dead
		Stat status = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		status.HP -= 10;

		script.SpawnPrefab(L"prefab\\GhostDead.prefab", 0, GetOwner()->Transform()->GetWorldPos(), 0.5f);
		GetOwner()->SetLifeSpan(0.f);
	}
}

void CGhostHit::OnOverlap(CCollider2D* _Other)
{
}

void CGhostHit::EndOverlap(CCollider2D* _Other)
{
}
