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
			if (GetOwner()->GetName() == L"Trap1")
			{
				CGameObject* door = script.SpawnandReturnPrefab(L"prefab\\Fense", (int)LAYER::ITEM, Vec3(3622.f, 608.f, 1409.f));
				door->Transform()->SetRelativeScale(Vec3(0.21f, 0.21f, 0.21f));
				Vec3 rot = (Vec3(270.f, 48.f, 0.f) / 180.f) * XM_PI;
				door->SetName(L"Fense");
				door->Transform()->SetRelativePos(rot);
				door->AddComponent(new CCollider3D);
				door->AddComponent(new CRigidbody);
				door->AddComponent(new CFenseScript);
				door->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
				door->MeshRender()->SetDynamicShadow(true);
				door->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(3622.f, 608.f, 1409.f), Vec3(100.f, 100.f, 100.f), door);
			}
			else if (GetOwner()->GetName() == L"Trap2")
			{
				CGameObject* door1 = script.SpawnandReturnPrefab(L"prefab\\Fense", (int)LAYER::ITEM, Vec3(2515.f, 608.f, 2143.f));
				door1->Transform()->SetRelativeScale(Vec3(0.21f, 0.21f, 0.21f));
				Vec3 rot = (Vec3(270.f, 41.f, 0.f) / 180.f) * XM_PI;
				door1->SetName(L"Fense");
				door1->Transform()->SetRelativePos(rot);
				door1->AddComponent(new CCollider3D);
				door1->AddComponent(new CRigidbody);
				door1->AddComponent(new CFenseScript);
				door1->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
				door1->MeshRender()->SetDynamicShadow(true);
				door1->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(2515.f, 608.f, 2143.f), Vec3(100.f, 100.f, 100.f), door1);//till here

				CGameObject* door2 = script.SpawnandReturnPrefab(L"prefab\\Fense", (int)LAYER::ITEM, Vec3(2864.f, 957.f, 3988.f));
				door2->Transform()->SetRelativeScale(Vec3(0.27f, 0.27f, 0.27f));
				Vec3 rot1 = (Vec3(270.f, -43.f, 0.f) / 180.f) * XM_PI;
				door2->SetName(L"Fense");
				door2->Transform()->SetRelativePos(rot1);
				door2->AddComponent(new CCollider3D);
				door2->AddComponent(new CRigidbody);
				door2->AddComponent(new CFenseScript);
				door2->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
				door2->MeshRender()->SetDynamicShadow(true);
				door2->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(2864.f, 957.f, 3988.f), Vec3(100.f, 100.f, 100.f), door2);

				CGameObject* door3 = script.SpawnandReturnPrefab(L"prefab\\Fense", (int)LAYER::ITEM, Vec3(807.f, 957.f, 3533.f));
				door3->Transform()->SetRelativeScale(Vec3(0.27f, 0.27f, 0.27f));
				Vec3 rot2 = (Vec3(270.f, 39.f, 0.f) / 180.f) * XM_PI;
				door3->SetName(L"Fense");
				door3->Transform()->SetRelativePos(rot2);
				door3->AddComponent(new CCollider3D);
				door3->AddComponent(new CRigidbody);
				door3->AddComponent(new CFenseScript);
				door3->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
				door3->MeshRender()->SetDynamicShadow(true);
				door3->MeshRender()->SetFrustumCheck(false);
				CPhysXMgr::GetInst()->CreateStaticCube(Vec3(807.f, 957.f, 3533.f), Vec3(100.f, 100.f, 100.f), door3);
			}

		}
		else if (curLevel->GetName() == L"Forest")
		{

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
