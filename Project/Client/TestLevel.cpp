#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>
#include <Engine\CEventMgr.h>
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
#include <Script\CFenseScript.h>
#include <Engine/CPhysXMgr.h>
#include <Script/CBatScript.h>
#include <Script\CGruntScript.h>
#include <Script/CLurkerScript.h>
#include <Script/CNaviTestScript.h>
#include <Script/CMainLightScript.h>

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

	pPlayer->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pPlayer->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 3.f));
	pPlayer->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 1.f));

	Stat PlayerStat;
	PlayerStat.Attack = 50.f;
	PlayerStat.Attack_Speed = 0.4f;
	PlayerStat.HP = 4;
	PlayerStat.Speed = 150.f;
	pPlayer->GetScript<CStateScript>()->SetStat(PlayerStat);
	CPhysXMgr::GetInst()->CreateSphere(Vec3(2500.f, 1000.f, 3000.f), 20.f, pPlayer);
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
	
	CPhysXMgr::GetInst()->CreateSphere(Vec3(1500.f, 1000.f, 3000.f), 20.f, pObject);
	SpawnGameObject(pObject, Vec3(1000.f, 1000.f, 1300.f), (int)LAYER::MONSTER);
	
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

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Anchor.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Anchor");
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);
	//
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Fence.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Fence");
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);

	//pObject = new CGameObject;
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CParticleSystem);
	//pObject->ParticleSystem()->SetTex(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\particle\\Fire2.png"));
	//pObject->ParticleSystem()->AnimationModule(56, 8, Vec2(0.f, 0.f), Vec2(256.f, 256.f), Vec2(0.f));
	//SpawnGameObject(pObject, Vec3(500.f, 500.f, 500.f), (int)LAYER::DEFAULT);

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Grunt.fbx");
	//CGameObject* pMonster = pMeshData->Instantiate();
	//pMonster->SetName(L"Monster");
	////pMonster->AddComponent(new CMonsterScript);
	////pMonster->AddComponent(new CStateScript);
	//pMonster->MeshRender()->SetDynamicShadow(true);
	//pMonster->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pMonster, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);
	 
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Player\\SLASH_L.fbx");
	//CGameObject* pSlash = pMeshData->Instantiate();
	//pSlash->SetName(L"SLASH_L");
	//pSlash->MeshRender()->SetDynamicShadow(true);
	//pSlash->MeshRender()->SetFrustumCheck(false);
	//pSlash->Transform()->SetRelativeScale(1.f, 1.f, 1.f);
	//
	//SpawnGameObject(pSlash, Vec3(0.f, 0.f, 0.f), (int)LAYER::PLAYERPROJECTILE);
	//
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Player\\SLASH_R.fbx");
	//pSlash = pMeshData->Instantiate();
	//pSlash->SetName(L"SLASH_R");
	//pSlash->MeshRender()->SetDynamicShadow(true);
	//pSlash->MeshRender()->SetFrustumCheck(false);
	//pSlash->Transform()->SetRelativeScale(40.f, 40.f, 40.f);
	//
	//SpawnGameObject(pSlash, Vec3(0.f, 0.f, 0.f), (int)LAYER::PLAYERPROJECTILE);

	//CGameObject* pHook = nullptr;
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Hook.fbx");
	//pHook = pMeshData->Instantiate();
	//pHook->SetName(L"Hook");
	//pHook->AddComponent(new CCollider3D);
	//pHook->AddComponent(new CMagic_HookScript);
	//
	//pHook->Transform()->SetRelativeScale(Vec3(0.3f));
	//
	//pHook->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pHook->Collider3D()->SetAbsolute(true);
	//pHook->Collider3D()->SetOffsetScale(Vec3(40.f));
	//
	//SpawnGameObject(pHook, Vec3(0.f, 0.f, 0.f), (int)LAYER::PLAYERPROJECTILE);
	// 
	//CGameObject* pArrow = nullptr;
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Player\\Arrow.fbx");
	//pArrow = pMeshData->Instantiate();
	//pArrow->SetName(L"Arrow");
	//pArrow->AddComponent(new CCollider3D);
	//pArrow->AddComponent(new CMagic_ArrowScript);
	//
	//pArrow->Transform()->SetRelativeScale(Vec3(0.4f));
	//
	//pArrow->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pArrow->Collider3D()->SetAbsolute(true);
	//pArrow->Collider3D()->SetOffsetScale(Vec3(40.f));
	//
	//SpawnGameObject(pArrow, Vec3(0.f, 0.f, 0.f), (int)LAYER::PLAYERPROJECTILE);

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::GROUND));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::FALLAREA));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::LADDER));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::ITEM));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::ANCHOR));
}
