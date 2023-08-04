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
#include <Script/CGameCameraScript.h>
#include <Script/CPlayerWeaponScript.h>
#include <Script/CLurkerScript.h>
#include <Engine/CPhysXMgr.h>
#include "CLevelSaveLoad.h"


void CreateTestLevel()
{

	//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	//pCurLevel->ChangeState(LEVEL_STATE::STOP);

	//// Layer 이름설정
	//pCurLevel->GetLayer(0)->SetName(L"DEFAULT");
	//pCurLevel->GetLayer(1)->SetName(L"MAINCAMERA");
	//pCurLevel->GetLayer(2)->SetName(L"SUBCAMERA");
	//pCurLevel->GetLayer(3)->SetName(L"PLAYER");
	//pCurLevel->GetLayer(4)->SetName(L"MONSTER");
	//pCurLevel->GetLayer(5)->SetName(L"PLAYERPROJECTILE");
	//pCurLevel->GetLayer(6)->SetName(L"MONSTERPROJECTILE");
	//pCurLevel->GetLayer(7)->SetName(L"WALL");
	//pCurLevel->GetLayer(8)->SetName(L"ITEM");
	//pCurLevel->GetLayer(9)->SetName(L"GROUND");
	//pCurLevel->GetLayer(10)->SetName(L"FALLAREA");
	//pCurLevel->GetLayer(11)->SetName(L"LADDER");
	//pCurLevel->GetLayer(12)->SetName(L"ANCHOR");
	//pCurLevel->GetLayer(13)->SetName(L"BRAIZER");
	//pCurLevel->GetLayer(14)->SetName(L"NPC");


	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CGameCameraScript);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
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

	// SkyBox 추가
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(100.f, 100.f, 100.f);
	pSkyBox->Transform()->SetRelativeRot(Vec3(0.f, XM_PI / 2.f, 0.f));

	pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::CUBE);
	pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\SkyWater.dds"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);

	// Decal Object
	//CGameObject* pDecal = new CGameObject;
	//pDecal->SetName(L"Decal");
	//pDecal->AddComponent(new CTransform);
	//pDecal->AddComponent(new CDecal);
	//
	//pDecal->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 200.f));
	//pDecal->Decal()->SetOutputTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\MagicCircle.png"));
	//pDecal->Decal()->SetAsLight(false);
	//
	//SpawnGameObject(pDecal, Vec3(0.f, 200.f, 0.f), (int)LAYER::DEFAULT);

	//CGameObject* pWall = new CGameObject;
	//pWall->SetName(L"Wall");
	//pWall->AddComponent(new CTransform);
	//pWall->AddComponent(new CMeshRender);
	//
	//pWall->Transform()->SetRelativeScale(3000.f, 3000.f, 3000.f);
	//
	//pWall->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pWall->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireMtrl"), 0);
	//pWall->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\noise\\noise_01.png"));
	//pWall->MeshRender()->GetMaterial(0)->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Fighter.bmp"));
	//pWall->MeshRender()->SetDynamicShadow(true);
	//pWall->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pWall, Vec3(0.f, 0.f, 0.f), (int)LAYER::GROUND);

	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pPlayer = nullptr;
	CGameObject* pObject = nullptr;
	//
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowPlayer.fbx");
	pPlayer = pMeshData->Instantiate();
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CPlayerScript);
	pPlayer->AddComponent(new CStateScript);
	pPlayer->AddComponent(new CCollider3D);
	pPlayer->AddComponent(new CRigidbody);

	pPlayer->Transform()->SetRelativeScale(Vec3(40.f, 40.f, 40.f));
	pPlayer->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	pPlayer->MeshRender()->SetDynamicShadow(true);
	pPlayer->MeshRender()->SetFrustumCheck(false);

	pPlayer->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pPlayer->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 3.f));
	pPlayer->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 1.f));

	Stat PlayerStat;
	PlayerStat.Attack = 50.f;
	PlayerStat.Attack_Speed = 0.4f;
	PlayerStat.HP = 4;
	PlayerStat.Speed = 150.f;
	pPlayer->GetScript<CStateScript>()->SetStat(PlayerStat);
	CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 500.f, 800.f), 20.f, pPlayer);
	SpawnGameObject(pPlayer, Vec3(0.f, 500.f, 0.f), (int)LAYER::PLAYER);

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowSword.fbx");
	CGameObject* pSword = pMeshData->Instantiate();
	pSword->SetName(L"Sword");
	pSword->AddComponent(new CPlayerWeaponScript);
	pSword->AddComponent(new CStateScript);
	pSword->AddComponent(new CCollider3D);
	pSword->MeshRender()->SetDynamicShadow(true);
	pSword->MeshRender()->SetFrustumCheck(false);
	pPlayer->AddChild(pSword);

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bow.fbx");
	CGameObject* pBow = pMeshData->Instantiate();
	pBow->SetName(L"Bow");
	pBow->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	pBow->MeshRender()->SetDynamicShadow(true);
	pBow->MeshRender()->SetFrustumCheck(false);
	pPlayer->AddChild(pBow);

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Lurker.fbx");
	pObject = pMeshData->Instantiate();
	pObject->SetName(L"Lurker");
	pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CRigidbody);
	pObject->AddComponent(new CLurkerScript);
	pObject->AddComponent(new CStateScript);

	pObject->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);
	pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));

	pObject->MeshRender()->SetDynamicShadow(true);
	pObject->MeshRender()->SetFrustumCheck(false);

	CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 500.f, 3000.f), 20.f, pObject);
	SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::MONSTER);

	CLevelSaveLoad script;
	CGameObject* pSerch = script.LoadPrefab(L"prefab\\MonsterDetectRange.prefab");
	pObject->AddChild(pSerch);


	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\PhysXmap\\Castle_Simple.fbx");
	pObject = pMeshData->Instantiate();
	CPhysXMgr::GetInst()->ConvertStatic(Vec3(0.f, 0.f, 0.f), pObject);

	delete pObject;

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Castle.fbx");
	pObject = pMeshData->Instantiate();
	pObject->SetName(L"Map");
	pObject->MeshRender()->SetDynamicShadow(true);
	pObject->MeshRender()->SetFrustumCheck(false);
	SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);


	return;
	//CCollisionMgr::GetInst()->LayerCheck(L"PLAYER", L"MONSTER");
	//CCollisionMgr::GetInst()->LayerCheck(L"PLAYER", L"MONSTERPROJECTILE");
	//CCollisionMgr::GetInst()->LayerCheck(L"PLAYER", L"NPC");
	//CCollisionMgr::GetInst()->LayerCheck(L"MONSTER", L"PLAYERPROJECTILE");

	//{
	//	CLevel* pNewLevel = CLevelSaveLoad::Stop(L"Level\\HallMap.lv", LEVEL_STATE::STOP);
	//	pNewLevel->SetName(L"HallMap");
	//	tEvent evn = {};
	//	evn.Type = EVENT_TYPE::LEVEL_CHANGE;
	//	evn.wParam = (DWORD_PTR)pNewLevel;
	//	CEventMgr::GetInst()->AddEvent(evn);

	//	///*CLevelMgr::GetInst()->SavePlayerInfo(1, 1000, 1000, 500, 500, 0, 100, 2, 1, 10);
	//	//Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\203680770.wem");
	//	//pSound->Play(1, 0.5f, false);*/
	//}

	//Ptr<CMeshData> pMeshData = nullptr;
	//CGameObject* pObj = nullptr;

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowSword.fbx");
	//pObj = pMeshData->Instantiate();
	//pObj->SetName(L"Sword");
	//pObj->MeshRender()->SetDynamicShadow(true);
	//pObj->MeshRender()->SetFrustumCheck(false);
	//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);
	//CPhysXMgr::GetInst()->CreateCube(pObj->Transform()->GetWorldPos(), pObj->Transform()->GetRelativeScale(), pObj);
	//// SkyBox 추가
	///*{
	//	CGameObject* pSkyBox = new CGameObject;
	//	pSkyBox->SetName(L"SkyBox");

	//	pSkyBox->AddComponent(new CTransform);
	//	pSkyBox->AddComponent(new CSkyBox);

	//	pSkyBox->Transform()->SetRelativeScale(100.f, 100.f, 100.f);
	//	pSkyBox->Transform()->SetRelativeRot(Vec3(0.f, XM_PI / 2.f, 0.f));

	//	pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::CUBE);
	//	pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\SkyWater.dds"));

	//	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);
	//}*/
	//

	return;
	

	//{
	//	Ptr<CMeshData> pMeshData = nullptr;
	//	CGameObject* pObj = nullptr;

	//	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bat.fbx");
	//	pObj = pMeshData->Instantiate();
	//	pObj->SetName(L"Bat");
	//	pObj->MeshRender()->SetDynamicShadow(true);
	//	pObj->MeshRender()->SetFrustumCheck(false);
	//	SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);
	//}

	//// Main Camera Object 생성
	//CGameObject* pMainCam = new CGameObject;
	//pMainCam->SetName(L"MainCamera");

	//pMainCam->AddComponent(new CTransform);
	//pMainCam->AddComponent(new CCamera);
	//pMainCam->AddComponent(new CCameraMoveScript);

	//pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	//pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	//pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	//pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	//SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 10);


	//// 광원 추가
	//CGameObject* pLightObj = new CGameObject;
	//pLightObj->SetName(L"Light");

	//pLightObj->AddComponent(new CTransform);
	//pLightObj->AddComponent(new CLight3D);

	//pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLightObj->Light3D()->SetLightDirection(Vec3(1.f, -1.f, 1.f));

	//pLightObj->Light3D()->SetRadius(500.f);
	//pLightObj->Light3D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	////pLightObj->Light3D()->SetLightSpecular(Vec3(0.3f, 0.3f, 0.3f));
	//pLightObj->Light3D()->SetLightAmbient(Vec3(0.15f, 0.15f, 0.15f));

	//SpawnGameObject(pLightObj, -pLightObj->Light3D()->GetLightDirection() * 1000.f, (int)LAYER::DEFAULT);

	//

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
