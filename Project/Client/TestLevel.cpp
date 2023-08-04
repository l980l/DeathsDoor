#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>
#include <Engine/CMeshData.h>
#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>
#include <Engine\CEventMgr.h>

#include <Script\CPlayerScript.h>
#include <Script/CStateScript.h>
#include <Script\CMonsterScript.h>
#include <Script/CCameraMoveScript.h>


#include "CLevelSaveLoad.h"


void CreateTestLevel()
{

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"DEFAULT");
	pCurLevel->GetLayer(1)->SetName(L"MAINCAMERA");
	pCurLevel->GetLayer(2)->SetName(L"SUBCAMERA");
	pCurLevel->GetLayer(3)->SetName(L"PLAYER");
	pCurLevel->GetLayer(4)->SetName(L"MONSTER");
	pCurLevel->GetLayer(5)->SetName(L"PLAYERPROJECTILE");
	pCurLevel->GetLayer(6)->SetName(L"MONSTERPROJECTILE");
	pCurLevel->GetLayer(7)->SetName(L"WALL");
	pCurLevel->GetLayer(8)->SetName(L"ITEM");
	pCurLevel->GetLayer(9)->SetName(L"GROUND");
	pCurLevel->GetLayer(10)->SetName(L"FALLAREA");
	pCurLevel->GetLayer(11)->SetName(L"LADDER");
	pCurLevel->GetLayer(12)->SetName(L"ANCHOR");
	pCurLevel->GetLayer(13)->SetName(L"BRAIZER");
	pCurLevel->GetLayer(14)->SetName(L"NPC");


	CCollisionMgr::GetInst()->LayerCheck(L"PLAYER", L"MONSTER");
	CCollisionMgr::GetInst()->LayerCheck(L"PLAYER", L"MONSTERPROJECTILE");
	CCollisionMgr::GetInst()->LayerCheck(L"PLAYER", L"NPC");
	CCollisionMgr::GetInst()->LayerCheck(L"MONSTER", L"PLAYERPROJECTILE");

	{
		CLevel* pNewLevel = CLevelSaveLoad::Stop(L"Level\\HallMap.lv", LEVEL_STATE::STOP);
		pNewLevel->SetName(L"HallMap");
		tEvent evn = {};
		evn.Type = EVENT_TYPE::LEVEL_CHANGE;
		evn.wParam = (DWORD_PTR)pNewLevel;
		CEventMgr::GetInst()->AddEvent(evn);

		///*CLevelMgr::GetInst()->SavePlayerInfo(1, 1000, 1000, 500, 500, 0, 100, 2, 1, 10);
		//Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\203680770.wem");
		//pSound->Play(1, 0.5f, false);*/
	}

	//Ptr<CMeshData> pMeshData = nullptr;
	//CGameObject* pObj = nullptr;

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\GrimKnight.fbx");
	//pObj = pMeshData->Instantiate();
	//pObj->SetName(L"GrimKinght");
	//pObj->MeshRender()->SetDynamicShadow(true);
	//pObj->MeshRender()->SetFrustumCheck(false);
	//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);

	// SkyBox 추가
	/*{
		CGameObject* pSkyBox = new CGameObject;
		pSkyBox->SetName(L"SkyBox");

		pSkyBox->AddComponent(new CTransform);
		pSkyBox->AddComponent(new CSkyBox);

		pSkyBox->Transform()->SetRelativeScale(100.f, 100.f, 100.f);
		pSkyBox->Transform()->SetRelativeRot(Vec3(0.f, XM_PI / 2.f, 0.f));

		pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::CUBE);
		pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\SkyWater.dds"));

		SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);
	}*/
	

	return;
	

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;

		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bat.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Bat");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);
		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);
	}

	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CCameraMoveScript);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 10);


	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light3D()->SetLightDirection(Vec3(1.f, -1.f, 1.f));

	pLightObj->Light3D()->SetRadius(500.f);
	pLightObj->Light3D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	//pLightObj->Light3D()->SetLightSpecular(Vec3(0.3f, 0.3f, 0.3f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.15f, 0.15f, 0.15f));

	SpawnGameObject(pLightObj, -pLightObj->Light3D()->GetLightDirection() * 1000.f, (int)LAYER::DEFAULT);

	

	{
		//// Decal Object
	//CGameObject* pDecal = new CGameObject;
	//pDecal->SetName(L"Decal");
	//pDecal->AddComponent(new CTransform);
	//pDecal->AddComponent(new CDecal);

	//pDecal->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 200.f));
	//pDecal->Decal()->SetOutputTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\MagicCircle.png"));
	//pDecal->Decal()->SetAsLight(false);

	//SpawnGameObject(pDecal, Vec3(0.f, 200.f, 0.f), (int)LAYER::DEFAULT);


	//CGameObject* pObject = new CGameObject;
	//pObject->SetName(L"Player");
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CRigidbody);
	//pObject->AddComponent(new CPlayerScript);
	//pObject->AddComponent(new CStateScript);

	//pObject->Transform()->SetRelativeScale(Vec3(500.f, 500.f, 500.f));

	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	//pObject->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));

	//pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);
	////pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"TILE_03"));
	////pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"TILE_03_N"));
	//pObject->MeshRender()->SetDynamicShadow(true);

	//SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::PLAYER);


	//pObject = new CGameObject;
	//pObject->SetName(L"Monster");
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	//pObject->AddComponent(new CMonsterScript);
	//pObject->AddComponent(new CStateScript);

	//pObject->Transform()->SetRelativeScale(Vec3(500.f, 500.f, 500.f));

	//pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	//pObject->MeshRender()->SetDynamicShadow(true);

	//SpawnGameObject(pObject, Vec3(500.f, 0.f, 300.f), (int)LAYER::MONSTER);
	}
	

	// ============
	// FBX Loading
	// ============	
	//{
	//	Ptr<CMeshData> pMeshData = nullptr;
	//	CGameObject* pObj = nullptr;
	//	
	//	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Knight.fbx");
	//	pObj = pMeshData->Instantiate();
	//	pObj->SetName(L"Knight");
	//	pObj->MeshRender()->SetDynamicShadow(true);
	//	pObj->MeshRender()->SetFrustumCheck(false);
	//	SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);
	//}
	/*
	{
	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pObj = nullptr;

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Knight.fbx");
	pObj = pMeshData->Instantiate();
	pObj->SetName(L"Knight");
	pObj->MeshRender()->SetDynamicShadow(true);
	pObj->MeshRender()->SetFrustumCheck(false);
	SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);
	}*/
	// 충돌 시킬 레이어 짝 지정
	
}
