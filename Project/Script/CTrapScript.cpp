#include "pch.h"
#include "CTrapScript.h"
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CPhysXMgr.h>
#include "CLevelSaveLoadInScript.h"
#include "CFenseScript.h"

void CTrapScript::begin()
{
}

void CTrapScript::tick()
{
}

void CTrapScript::BeginOverlap(CCollider3D* _Other)
{
	CLevelSaveLoadInScript script;
	CLevel* curLevel = CLevelMgr::GetInst()->GetCurLevel();
	if (_Other->GetOwner()->GetName() == L"Player")
	{
		if (curLevel->GetName() == L"Castle")
		{
			if (GetOwner()->GetName() == L"Trap2")
			{
				CGameObject* door = script.SpawnandReturnPrefab(L"prefab\\Fence.prefab", (int)LAYER::ITEM, Vec3(3622.f, 608.f, 1409.f));
				door->Transform()->SetRelativeScale(Vec3(0.21f, 0.21f, 0.21f));
				Vec3 rot = (Vec3(270.f, 48.f, 0.f) / 180.f) * XM_PI;
				door->SetName(L"Fence");
				door->Transform()->SetRelativeRot(rot);
				door->AddComponent(new CRigidbody);
				door->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
				door->MeshRender()->SetDynamicShadow(true);
				door->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(3622.f, 608.f, 1409.f), Vec3(100.f, 100.f, 100.f), door);
			}
			else if (GetOwner()->GetName() == L"Trap1")
			{
				CGameObject* door1 = script.SpawnandReturnPrefab(L"prefab\\Fence.prefab", (int)LAYER::ITEM, Vec3(2515.f, 608.f, 2143.f));
				door1->Transform()->SetRelativeScale(Vec3(0.21f, 0.21f, 0.21f));
				Vec3 rot = (Vec3(270.f, 41.f, 0.f) / 180.f) * XM_PI;
				door1->SetName(L"Fence1");
				door1->Transform()->SetRelativeRot(rot);
				door1->AddComponent(new CRigidbody);
				door1->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
				door1->MeshRender()->SetDynamicShadow(true);
				door1->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(2515.f, 608.f, 2143.f), Vec3(100.f, 100.f, 100.f), door1);//till here

				CGameObject* door2 = script.SpawnandReturnPrefab(L"prefab\\Fence.prefab", (int)LAYER::ITEM, Vec3(2864.f, 957.f, 3988.f));
				door2->Transform()->SetRelativeScale(Vec3(0.27f, 0.27f, 0.27f));
				Vec3 rot1 = (Vec3(270.f, -43.f, 0.f) / 180.f) * XM_PI;
				door2->SetName(L"Fence2");
				door2->Transform()->SetRelativeRot(rot1);
				door2->AddComponent(new CRigidbody);
				door2->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
				door2->MeshRender()->SetDynamicShadow(true);
				door2->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(2864.f, 957.f, 3988.f), Vec3(100.f, 100.f, 100.f), door2);

				CGameObject* door3 = script.SpawnandReturnPrefab(L"prefab\\Fence.prefab", (int)LAYER::ITEM, Vec3(807.f, 957.f, 3533.f));
				door3->Transform()->SetRelativeScale(Vec3(0.27f, 0.27f, 0.27f));
				Vec3 rot2 = (Vec3(270.f, 39.f, 0.f) / 180.f) * XM_PI;
				door3->SetName(L"Fence3");
				door3->Transform()->SetRelativeRot(rot2);
				door3->AddComponent(new CRigidbody);
				door3->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
				door3->MeshRender()->SetDynamicShadow(true);
				door3->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(807.f, 957.f, 3533.f), Vec3(100.f, 100.f, 100.f), door3);
			}

		}
		else if (curLevel->GetName() == L"Forest")
		{
			if (GetOwner()->GetName() == L"Trap1")
			{
				CGameObject* door = script.SpawnandReturnPrefab(L"prefab\\Fence.prefab", (int)LAYER::ITEM, Vec3(5942.f, 549.f, 3636.f));
				door->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
				Vec3 rot = (Vec3(270.f, 89.f, 0.f) / 180.f) * XM_PI;
				door->SetName(L"Fence");
				door->Transform()->SetRelativeRot(rot);
				door->AddComponent(new CRigidbody);
				door->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
				door->MeshRender()->SetDynamicShadow(true);
				door->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(5942.f, 549.f, 3636.f), Vec3(500.f, 500.f, 500.f), door);

				CGameObject* door1 = script.SpawnandReturnPrefab(L"prefab\\Fence.prefab", (int)LAYER::ITEM, Vec3(5811.f, 550.f, 6159.f));
				door1->Transform()->SetRelativeScale(Vec3(0.4f, 0.4f, 0.4f));
				Vec3 rot = (Vec3(270.f, 89.f, 0.f) / 180.f) * XM_PI;
				door1->SetName(L"Fence1");
				door1->Transform()->SetRelativeRot(rot);
				door1->AddComponent(new CRigidbody);
				door1->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
				door1->MeshRender()->SetDynamicShadow(true);
				door1->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(5811.f, 550.f, 6159.f), Vec3(200.f, 200.f, 200.f), door1);//till here
			}
		}

		GetOwner()->SetLifeSpan(0.f);
	}
	

}

CTrapScript::CTrapScript()		:
	CScript(SCRIPT_TYPE::TRAPSCRIPT)
{
}

CTrapScript::~CTrapScript()
{
}
