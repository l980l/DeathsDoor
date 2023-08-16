#include "pch.h"
#include "CTrapScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CPhysXMgr.h>
#include "CLevelSaveLoadInScript.h"
#include "CFenseScript.h"
#include "CSpawnMgr.h"
#include "CRoomScript.h"

void CTrapScript::begin()
{
	m_bTrapped == false;
}

void CTrapScript::tick()
{
	if (m_bTrapped)
	{
		//GetOwner()->GetScript<CRoomScript>()->ReduceMonsterCount();
	}
	
}

void CTrapScript::BeginOverlap(CCollider3D* _Other)
{
	CLevelSaveLoadInScript script;
	CLevel* curLevel = CLevelMgr::GetInst()->GetCurLevel();
	if (_Other->GetOwner()->GetName() == L"Player")
	{
		if (curLevel->GetLevelType() == (int)LEVEL_TYPE::CASTLE_FIELD)
		{
			if (GetOwner()->GetName() == L"Trap1" && m_bTrapped == false)
			{

				GetOwner()->GetScript<CRoomScript>()->SetRoomNum(1);
				GetOwner()->GetScript<CRoomScript>()->SetWaveCount(2);//최대 웨이브 수
				
				vector<SpawnInfo> wave0 = {};
				SpawnInfo info;
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(2344.f, 630.f, 3000.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(2600.f, 630.f, 2600.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(1549.f, 630.f, 3000.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(1941.f, 630.f, 2442.f);
				wave0.push_back(info);

				vector<SpawnInfo> wave1;
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(2299.f, 630.f, 3074.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(1889.f, 630.f, 2680.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(1574.f, 630.f, 3047.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(1940.f, 630.f, 3440.f);
				wave1.push_back(info);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[0].PrefabName, wave0[0].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[1].PrefabName, wave0[1].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[2].PrefabName, wave0[2].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[3].PrefabName, wave0[3].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[0].PrefabName, wave1[0].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[1].PrefabName, wave1[1].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[2].PrefabName, wave1[2].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[3].PrefabName, wave1[3].SpawnPos);
				
				CSpawnMgr::GetInst()->RegisterWave(1, GetOwner()->GetScript<CRoomScript>());
				CSpawnMgr::GetInst()->SpawnMonster(1);
				m_bTrapped = true;
				
				//trapped 되었으면 fence를 오픈하고 rigidbody PhysX설정해준다
				
				CGameObject* door1 = CLevelMgr::GetInst()->FindObjectByName(L"Fence1");
				door1->GetScript<CFenseScript>()->SetRoomNum(1);
				door1->MeshRender()->SetDynamicShadow(true);
				door1->MeshRender()->SetFrustumCheck(false);

				CGameObject* door2 = CLevelMgr::GetInst()->FindObjectByName(L"Fence2");
				door2->GetScript<CFenseScript>()->SetRoomNum(1);
				door2->MeshRender()->SetDynamicShadow(true);
				door2->MeshRender()->SetFrustumCheck(false);

				CGameObject* door3 = CLevelMgr::GetInst()->FindObjectByName(L"Fence3");
				door3->GetScript<CFenseScript>()->SetRoomNum(1);
				door3->MeshRender()->SetDynamicShadow(true);
				door3->MeshRender()->SetFrustumCheck(false);

				CSpawnMgr::GetInst()->RegisterFence(1, door1);
				CSpawnMgr::GetInst()->RegisterFence(1, door2);
				CSpawnMgr::GetInst()->RegisterFence(1, door3);
				CSpawnMgr::GetInst()->SetFence(1, true);//연다
				
				
			}
			else if (GetOwner()->GetName() == L"Trap2" && m_bTrapped == false)
			{
				GetOwner()->GetScript<CRoomScript>()->SetRoomNum(2);
				GetOwner()->GetScript<CRoomScript>()->SetWaveCount(2);//최대 웨이브 수

				vector<SpawnInfo> wave0 = {};
				SpawnInfo info;
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(3760.f, 630.f, 719.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(4064.f, 630.f, 719.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(4004.f, 630.f, 961.f);
				wave0.push_back(info);

				vector<SpawnInfo> wave1;
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(3760.f, 630.f, 719.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(4064.f, 630.f, 719.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Bat.prefab";
				info.SpawnPos = Vec3(4004.f, 630.f, 961.f);
				wave1.push_back(info);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[0].PrefabName, wave0[0].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[1].PrefabName, wave0[1].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[2].PrefabName, wave0[2].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[0].PrefabName, wave1[0].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[1].PrefabName, wave1[1].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[2].PrefabName, wave1[2].SpawnPos);

				CSpawnMgr::GetInst()->RegisterWave(2, GetOwner()->GetScript<CRoomScript>());
				CSpawnMgr::GetInst()->SpawnMonster(2);
				m_bTrapped = true;

				//trapped 되었으면 fence를 오픈하고 rigidbody PhysX설정해준다

				CGameObject* door4 = CLevelMgr::GetInst()->FindObjectByName(L"Fence4");
				door4->GetScript<CFenseScript>()->SetRoomNum(2);
				door4->MeshRender()->SetDynamicShadow(true);
				door4->MeshRender()->SetFrustumCheck(false);

				CSpawnMgr::GetInst()->RegisterFence(2, door4);
				CSpawnMgr::GetInst()->SetFence(2, true);//연다
				
			}

		}
		else if (curLevel->GetLevelType() == (int)LEVEL_TYPE::FOREST_FIELD)
		{
			if (GetOwner()->GetName() == L"Trap1" && m_bTrapped == false)
			{
				
				//=========================
				GetOwner()->GetScript<CRoomScript>()->SetRoomNum(1);
				GetOwner()->GetScript<CRoomScript>()->SetWaveCount(2);//최대 웨이브 수

				vector<SpawnInfo> wave0 = {};
				SpawnInfo info;
				info.PrefabName = L"prefab\\Bazooka.prefab";
				info.SpawnPos = Vec3(3933.f, 630.f, 5529.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Lurker.prefab";
				info.SpawnPos = Vec3(2330.f, 630.f, 4916.f);
				wave0.push_back(info);
				info.PrefabName = L"prefab\\Lurker.prefab";
				info.SpawnPos = Vec3(3169.f, 630.f, 4526.f);
				wave0.push_back(info);

				vector<SpawnInfo> wave1;
				info.PrefabName = L"prefab\\Bazooka.prefab";
				info.SpawnPos = Vec3(3933.f, 630.f, 5529.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Bazooka.prefab";
				info.SpawnPos = Vec3(2330.f, 630.f, 4916.f);
				wave1.push_back(info);
				info.PrefabName = L"prefab\\Lurker.prefab";
				info.SpawnPos = Vec3(3169.f, 630.f, 4526.f);
				wave1.push_back(info);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[0].PrefabName, wave0[0].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[1].PrefabName, wave0[1].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(0, wave0[2].PrefabName, wave0[2].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[0].PrefabName, wave1[0].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[1].PrefabName, wave1[1].SpawnPos);
				GetOwner()->GetScript<CRoomScript>()->AddWaveMst(1, wave1[2].PrefabName, wave1[2].SpawnPos);

				CSpawnMgr::GetInst()->RegisterWave(1, GetOwner()->GetScript<CRoomScript>());
				CSpawnMgr::GetInst()->SpawnMonster(1);
				m_bTrapped = true;

				//trapped 되었으면 fence를 오픈하고 rigidbody PhysX설정해준다

				CGameObject* door1 = CLevelMgr::GetInst()->FindObjectByName(L"Fence1");
				door1->GetScript<CFenseScript>()->SetRoomNum(1);
				door1->MeshRender()->SetDynamicShadow(true);
				door1->MeshRender()->SetFrustumCheck(false);

				CGameObject* door2 = CLevelMgr::GetInst()->FindObjectByName(L"Fence2");
				door2->GetScript<CFenseScript>()->SetRoomNum(1);
				door2->MeshRender()->SetDynamicShadow(true);
				door2->MeshRender()->SetFrustumCheck(false);


				CSpawnMgr::GetInst()->RegisterFence(1, door1);
				CSpawnMgr::GetInst()->RegisterFence(1, door2);
				CSpawnMgr::GetInst()->SetFence(1, true);//연다
			}
			/*else if (GetOwner()->GetName() == L"Trap2" && m_bTrapped == false)
			{
				GetOwner()->GetScript<CRoomScript>()->SetRoomNum(2);

				CGameObject* door1 = CLevelMgr::GetInst()->FindObjectByName(L"Fence3");
				door1->GetScript<CFenseScript>()->SetRoomNum(2);
				door1->MeshRender()->SetDynamicShadow(true);
				door1->MeshRender()->SetFrustumCheck(false);

				CGameObject* door2 = CLevelMgr::GetInst()->FindObjectByName(L"Fence4");
				door2->GetScript<CFenseScript>()->SetRoomNum(2);
				door2->MeshRender()->SetDynamicShadow(true);
				door2->MeshRender()->SetFrustumCheck(false);
			}*/
		}
		
		
	}
	

}

CTrapScript::CTrapScript()		:
	CScript(SCRIPT_TYPE::TRAPSCRIPT)
{
}

CTrapScript::~CTrapScript()
{
}
