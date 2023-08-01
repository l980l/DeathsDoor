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
	
	//player�� HP ���� �޾ƿ���
	Stat playerStatus = playerStatusScript->GetStat();
	m_pMaxHP = playerStatus.MAXHP;
	m_pHP = playerStatus.HP;
	
	//HP Frame�� HP empty icon ��ġ
	CLevelSaveLoadInScript script;

	script.SpawnPrefab(L"texture\\HUD\\HPFrame.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_hp_empty 1.png", 0, Vec3(0.f, 0.f, 0.f));

	//Player�� energy ���� �޾ƿ���
	m_pMaxEnergy = playerStatus.MAXEnergy;
	m_pEnergy = playerStatus.Energy;

	//energy empty icon ��ġ
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));
	script.SpawnPrefab(L"texture\\HUD\\hud_energy_empty.png", 0, Vec3(0.f, 0.f, 0.f));

	//���� ���� Ÿ�� Icon ��ġ
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
	//������ �̿��ϸ� HUD ���� -> �������� ������ ���� UI Camera ���� �� ����
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		GetOwner()->SetLifeSpan(0.f);
	}
	
	//���� Magic Active Type�� Ȯ���ϰ� Active icon���� ��ȯ
	if ((UINT)PLAYER_MAGIC::ARROW == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//������ �ٸ� ���������� Active�Ǿ��ִٸ�, DA icon���� ����
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

		//���� ���� ������ DA icon�� ����
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"ArrowDA");
		arrowDA->SetLifeSpan(0.f);
		
		//���� ���� ������ Active icon�� spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\ArrowActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"ArrowActive");
	}
	else if ((UINT)PLAYER_MAGIC::FIRE == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//������ �ٸ� ���������� Active�Ǿ��ִٸ�, DA icon���� ����
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

		//���� ���� ������ DA icon�� ����
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"FireDA");
		arrowDA->SetLifeSpan(0.f);

		//���� ���� ������ Active icon�� spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\FireActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"FireActive");
	}
	else if ((UINT)PLAYER_MAGIC::BOMB == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//������ �ٸ� ���������� Active�Ǿ��ִٸ�, DA icon���� ����
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

		//���� ���� ������ DA icon�� ����
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"BombDA");
		arrowDA->SetLifeSpan(0.f);

		//���� ���� ������ Active icon�� spawn
		CGameObject* object = script.SpawnandReturnPrefab(L"texture\\HUD\\BombActive.png", 0, Vec3(0.f, 0.f, 0.f));
		object->SetName(L"BombActive");
	}
	else if ((UINT)PLAYER_MAGIC::HOOK == m_pMagicType)
	{
		CLevelSaveLoadInScript script;

		//������ �ٸ� ���������� Active�Ǿ��ִٸ�, DA icon���� ����
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

		//���� ���� ������ DA icon�� ����
		CGameObject* arrowDA = CLevelMgr::GetInst()->FindObjectByName(L"HookDA");
		arrowDA->SetLifeSpan(0.f);

		//���� ���� ������ Active icon�� spawn
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
	//Point -> monster�� dead �� �� ���� GetDigitCount --> ShowMoney ��� Money�� ���⿡�� spawn���� �ʴ´�.
}
