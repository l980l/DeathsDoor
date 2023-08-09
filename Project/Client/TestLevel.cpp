#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CStateScript.h>
#include <Script\CMonsterScript.h>
#include <Script\CCameraMoveScript.h>
#include <Script\CPlayerWeaponScript.h>
#include <Script\CGameCameraScript.h>
#include <Script\CMagic_ArrowScript.h>
#include <Script\CMagic_BombScript.h>
#include <Script\CMagic_FireScript.h>
#include <Script\CMagic_HookScript.h>
#include <Engine/CPhysXMgr.h>
#include <Script/CBatScript.h>
#include <Script\CGruntScript.h>
#include <Script/CLurkerScript.h>
#include <Script\CBazookaScript.h>
#include <Script/CNaviTestScript.h>
#include <Script/CMainLightScript.h>
#include <Script/CWaterCameraScript.h>
#include <Script/CCrowBossScript.h>
#include <Script/CSlashScript.h>

#include "CLevelSaveLoad.h"


void CreateTestLevel()
{

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
	pLightObj->AddComponent(new CMainLightScript);

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


	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pPlayer = nullptr; 
	CGameObject* pObject = nullptr;
	
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
	
	pPlayer->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pPlayer->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	pPlayer->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 1.f));
	
	Stat PlayerStat;
	PlayerStat.Attack = 50.f;
	PlayerStat.Attack_Speed = 0.4f;
	PlayerStat.HP = 4;
	PlayerStat.Speed = 150.f;
	PlayerStat.Spell_Power = 40.f;
	pPlayer->GetScript<CStateScript>()->SetStat(PlayerStat);
	CPhysXMgr::GetInst()->CreateSphere(Vec3(2500.f, 1000.f, 3000.f), 20.f, pPlayer);
	SpawnGameObject(pPlayer, Vec3(0.f, 500.f, 0.f), (int)LAYER::PLAYER);
	
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowSword.fbx");
	CGameObject* pSword = pMeshData->Instantiate();
	pSword->SetName(L"Sword");
	pSword->AddComponent(new CPlayerWeaponScript);
	pSword->AddComponent(new CStateScript);
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

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Lurker.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Lurker");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CRigidbody);
	//pObject->AddComponent(new CLurkerScript);
	//pObject->AddComponent(new CStateScript);
	//
	//pObject->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);
	//pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));
	//
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//
	//CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 3500.f, 3000.f), 20.f, pObject);
	//SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::MONSTER);

	//CGameObject* pDetectRange = CLevelSaveLoad::SpawnandReturnPrefab(L"prefab//Grunt.prefab", (int)LAYER::MONSTER, Vec3(0.f));
	//pObject->AddChild(pDetectRange);

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Grunt.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Grunt");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CRigidbody);
	//pObject->AddComponent(new CGruntScript);
	//pObject->AddComponent(new CStateScript);
	//
	//pObject->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);
	//pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));
	//
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//
	//CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 500.f, 3000.f), 20.f, pObject);
	//SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::MONSTER);
	//
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Grunt.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Grunt1");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CRigidbody);
	//pObject->AddComponent(new CGruntScript);
	//pObject->AddComponent(new CStateScript);
	//
	//pObject->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);
	//pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));
	//
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//
	//CPhysXMgr::GetInst()->CreateSphere(Vec3(2200.f, 500.f, 3000.f), 20.f, pObject);
	//SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::MONSTER);

	/*pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bazooka.fbx");
	pObject = pMeshData->Instantiate();
	pObject->SetName(L"Bazooka");
	pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CRigidbody);
	pObject->AddComponent(new CBazookaScript);
	pObject->AddComponent(new CStateScript);

	pObject->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);
	pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetOffsetScale(Vec3(700.f, 700.f, 700.f));
	pObject->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 333.f));

	pObject->MeshRender()->SetDynamicShadow(true);
	pObject->MeshRender()->SetFrustumCheck(false);

	CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 500.f, 3000.f), 20.f, pObject);
	SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::MONSTER);*/

	/*pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowBoss.fbx");
	pObject = pMeshData->Instantiate();
	pObject->SetName(L"CrowBoss");
	pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CRigidbody);
	pObject->AddComponent(new CCrowBossScript);
	pObject->AddComponent(new CStateScript);

	pObject->Transform()->SetRelativeScale(3.f, 3.f, 3.f);
	pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetOffsetScale(Vec3(162.f, 270.f, 162.f));
	pObject->Collider3D()->SetOffsetPos(Vec3(0.f, 55.f, 97.f));

	pObject->MeshRender()->SetDynamicShadow(true);
	pObject->MeshRender()->SetFrustumCheck(false);

	CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 500.f, 3000.f), 20.f, pObject);
	SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::MONSTER);*/

	//// GasGrenade 
	//CGameObject* pGasGrenade = new CGameObject;
	//pGasGrenade->SetName(L"GasGrenade");
	//pGasGrenade->AddComponent(new CCollider3D);
	//pGasGrenade->AddComponent(new CTransform);
	//pGasGrenade->AddComponent(new CRigidbody);
	//pGasGrenade->Transform()->SetRelativeScale(Vec3(80.f, 80.f, 80.f));
	//pGasGrenade->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pGasGrenade->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	//pGasGrenade->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));

	//CPhysXMgr::GetInst()->CreateSphere(Vec3(2000.f, 500.f, 3000.f), 40.f, pGasGrenade);
	//SpawnGameObject(pGasGrenade, Vec3(0.f, 500.f, 500.f), (int)LAYER::MONSTERPROJECTILE);

	// LoadingUI 
	//CGameObject* pLoadingUI = new CGameObject;
	//pLoadingUI->SetName(L"LoadingUI");
	//pLoadingUI->AddComponent(new CTransform);
	//pLoadingUI->AddComponent(new CMeshRender);
	//pLoadingUI->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pLoadingUI->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FlickerMtrl"), 0);
	//pLoadingUI->Transform()->SetRelativeScale(300.f, 300.f, 0.f);
	//pLoadingUI->MeshRender()->SetFrustumCheck(false);
	//pLoadingUI->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture/Deaths_Door/dd_icon_loading.png").Get());
	//SpawnGameObject(pLoadingUI, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);


	// Wind 
	//CGameObject* pWind = new CGameObject;
	//pWind->SetName(L"Wind");
	//pWind->AddComponent(new CTransform);
	//pWind->AddComponent(new CMeshRender);
	//pWind->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pWind->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"WindMtrl"), 0);
	//pWind->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pWind, Vec3(400.f, 500.f, 1000.f), (int)LAYER::DEFAULT);

	// Water 
	//CGameObject* pWater = new CGameObject;
	//pWater->SetName(L"Water");
	//pWater->AddComponent(new CTransform);
	//pWater->AddComponent(new CMeshRender);
	//pWater->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pWater->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"WaterMtrl"), 0);
	//pWater->Transform()->SetRelativeScale(8000.f, 8000.f, 8000.f);
	//pWater->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pWater, Vec3(4000.f, 520, 4000.f), (int)LAYER::DEFAULT);
	//
	//// Water Camera Object 생성
	//CGameObject* pWaterCam = new CGameObject;
	//pWaterCam->SetName(L"WaterCamera");
	//
	//pWaterCam->AddComponent(new CTransform);
	//pWaterCam->AddComponent(new CCamera);
	//pWaterCam->AddComponent(new CWaterCameraScript);
	//
	//pWaterCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	//pWaterCam->Camera()->SetCameraIndex(1);
	//pWaterCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	//pWaterCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.
	//pWaterCam->Camera()->SetWaterCamera(true);
	//
	//SpawnGameObject(pWaterCam, Vec3(0.f, 0.f, 0.f), 10);


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

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Player\\Slash_L.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Slash_L");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CSlashScript);
	//
	//pObject->Transform()->SetRelativeScale(Vec3(0.f));
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);
	//
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Player\\Slash_R.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Slash_R");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CSlashScript);
	//
	//pObject->Transform()->SetRelativeScale(Vec3(0.f));
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);

	//CGameObject* pObj = new CGameObject;
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CCollider3D);
	//pObj->SetName(L"Cube");
	//
	//pObj->Collider3D()->SetAbsolute(true);
	//pObj->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	//pObj->Collider3D()->SetOffsetScale(Vec3(500.f));
	//pObj->Collider3D()->SetDebugShape(true);
	//
	//SpawnGameObject(pObj, Vec3(3000.f, 500.f, 2500.f), (int)LAYER::MONSTER);
	//
	//pObj = new CGameObject;
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CCollider3D);
	//pObj->SetName(L"Sphere");
	//
	//pObj->Collider3D()->SetAbsolute(true);
	//pObj->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObj->Collider3D()->SetOffsetScale(Vec3(100.f));
	//pObj->Collider3D()->SetDebugShape(true);
	//
	//SpawnGameObject(pObj, Vec3(0.f), (int)LAYER::ANCHOR);

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::GROUND));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::FALLAREA));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::LADDER));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::ANCHOR));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::MONSTER));
}
