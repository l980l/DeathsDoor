#include "pch.h"
#include "TestLevel.h"

#include <Engine/CLevel.h>
#include <Engine/CGameObject.h>
#include <Engine/CResMgr.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CRenderMgr.h>
#include "CLevelSaveLoad.h"

void CreateTestLevel()
{
	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::MONSTER));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::GROUND));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::FALLAREA));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::LADDER));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::ITEM));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::NPC));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYER), static_cast<int>(LAYER::LEVELCHANGEDOOR));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::MONSTER), static_cast<int>(LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYERPROJECTILE), static_cast<int>(LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYERPROJECTILE), static_cast<int>(LAYER::ANCHOR));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYERPROJECTILE), static_cast<int>(LAYER::ITEM));
	CCollisionMgr::GetInst()->LayerCheck(static_cast<int>(LAYER::PLAYERPROJECTILE), static_cast<int>(LAYER::MONSTER));

	CLevel* NewLevel = CLevelSaveLoad::Stop(L"Level\\Start.lv", LEVEL_STATE::STOP);
	NewLevel->SetName(L"Start");
	NewLevel->SetLevelType(static_cast<int>(LEVEL_TYPE::START));

	//Player Status setting
	g_tPlayerStat.Attack = 50.f;
	g_tPlayerStat.Attack_Speed = 0.4f;
	g_tPlayerStat.MP = 4;
	g_tPlayerStat.Max_MP = 4;
	g_tPlayerStat.HP = 4;
	g_tPlayerStat.Max_HP = 4;
	g_tPlayerStat.Speed = 150.f;
	g_tPlayerStat.Spell_Power = 40.f;
	//=============================

	CRenderMgr::GetInst()->ClearCamera();
	CLevelMgr::GetInst()->ChangeLevel(NewLevel);
	NewLevel->ChangeState(LEVEL_STATE::PLAY);
}
