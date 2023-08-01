#include "pch.h"
#include "CHUDScript.h"
#include "CPlayerScript.h"
#include "CStateScript.h"
#include "CLevelSaveLoadInScript.h"

CHUDScript::CHUDScript()	:
	CScript(SCRIPT_TYPE::HUDSCRIPT)
{
}

CHUDScript::~CHUDScript()
{
}

void CHUDScript::begin()
{
	CStateScript* playerStatusScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CStateScript>();
	
	//player의 HP 정보 받아오기
	Stat playerStatus = playerStatusScript->GetStat();
	m_pMaxHP = playerStatus.MAXHP;
	m_pHP = playerStatus.HP;
	
	//HP Frame과 HP empty icon 배치
	CLevelSaveLoadInScript script;

	script.SpawnPrefab(L"texture\\HUD\\HPFrame.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));

	//Player의 energy 정보 받아오기
	m_pMaxEnergy = playerStatus.MAXEnergy;
	m_pEnergy = playerStatus.Energy;

	//energy empty icon 배치
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));

	//현재 마법 타입 Icon 배치
	CPlayerScript* playerScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
	m_pMagicType = playerScript->GetUseMagic();
	
	CGameObject* object1 = script.SpawnandReturnPrefab(L"texture\\HUD\\ArrowDA.png", 0, Vec3(0.f, 0.f, 0.f));
	object1->SetName(L"ArrowDA");
	CGameObject* object2 = script.SpawnandReturnPrefab(L"texture\\HUD\\FireDA.png", 0, Vec3(0.f, 0.f, 0.f));
	object2->SetName(L"FireDA");
	CGameObject* object3 = script.SpawnandReturnPrefab(L"texture\\HUD\\BombDA.png", 0, Vec3(0.f, 0.f, 0.f));
	object3->SetName(L"BombDA");
	CGameObject* object4 = script.SpawnandReturnPrefab(L"texture\\HUD\\HookDA.png", 0, Vec3(0.f, 0.f, 0.f));
	object4->SetName(L"HookDA");
}

void CHUDScript::tick()
{
	//상점을 이용하면 HUD 삭제 -> 상점에서 나오는 순간 UI Camera 에서 재 생성
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		GetOwner()->SetLifeSpan(0.f);
	}
	
	//현재 Magic Active Type을 확인하고 Active icon으로 전환
	if ((UINT)PLAYER_MAGIC::ARROW == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//기존에 다른 마법종류가 Active되어있다면, DA icon으로 변경
		if (CLevelMgr::GetInst()->FindObjectByName(L"FireActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"FireActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\FireDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"FireDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"BombActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"BombActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\BombDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"BombDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"HookActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"HookActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\HookDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"HookDA");
		}

		//현재 마법 종류의 DA icon을 해제
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"ArrowDA");
		arrowDA->SetLifeSpan(0.f);
		
		//현재 마법 종류의 Active icon을 spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\ArrowActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"ArrowActive");
	}
	else if ((UINT)PLAYER_MAGIC::FIRE == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//기존에 다른 마법종류가 Active되어있다면, DA icon으로 변경
		if (CLevelMgr::GetInst()->FindObjectByName(L"ArrowActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"ArrowActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\ArrowDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"ArrowDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"BombActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"BombActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\BombDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"BombDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"HookActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"HookActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\HookDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"HookDA");
		}

		//현재 마법 종류의 DA icon을 해제
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"FireDA");
		arrowDA->SetLifeSpan(0.f);

		//현재 마법 종류의 Active icon을 spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\FireActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"FireActive");
	}
	else if ((UINT)PLAYER_MAGIC::BOMB == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//기존에 다른 마법종류가 Active되어있다면, DA icon으로 변경
		if (CLevelMgr::GetInst()->FindObjectByName(L"ArrowActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"ArrowActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\ArrowDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"ArrowDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"FireActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"FireActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\FireDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"FireDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"HookActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"HookActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\HookDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"HookDA");
		}

		//현재 마법 종류의 DA icon을 해제
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"BombDA");
		arrowDA->SetLifeSpan(0.f);

		//현재 마법 종류의 Active icon을 spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\BombActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"BombActive");
	}
	else if ((UINT)PLAYER_MAGIC::HOOK == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//기존에 다른 마법종류가 Active되어있다면, DA icon으로 변경
		if (CLevelMgr::GetInst()->FindObjectByName(L"ArrowActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"ArrowActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\ArrowDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"ArrowDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"FireActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"FireActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\FireDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"FireDA");
		}
		if (CLevelMgr::GetInst()->FindObjectByName(L"BombActive"))
		{
			CLevelMgr::GetInst()->FindObjectByName(L"BombActive")->SetLifeSpan(0.f);
			CGameObject* obj = script.SpawnandReturnPrefab(L"texuture\\HUD\\BombDA", 0, Vec3(0.f, 0.f, 0.f));
			obj->SetName(L"BombDA");
		}

		//현재 마법 종류의 DA icon을 해제
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"HookDA");
		arrowDA->SetLifeSpan(0.f);

		//현재 마법 종류의 Active icon을 spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\HookActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"HookActive");
	}

	//HP
	CStateScript* playerStatusScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CStateScript>();
	Stat playerStatus = playerStatusScript->GetStat();
	m_pMaxHP = playerStatus.MAXHP;
	m_pHP = playerStatus.HP;
	//Energy
	m_pMaxEnergy = playerStatus.MAXEnergy;
	m_pEnergy = playerStatus.Energy;
	//Point -> monster가 dead 일 때 마다 GetDigitCount --> ShowMoney 고로 Money는 여기에서 spawn하지 않는다.
}
