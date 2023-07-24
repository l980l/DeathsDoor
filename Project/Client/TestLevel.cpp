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

#include "CLevelSaveLoad.h"


void CreateTestLevel()
{

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(10)->SetName(L"MainCamera");
	pCurLevel->GetLayer(11)->SetName(L"UICam");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");


	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CGameCameraScript);

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

	// SkyBox 추가
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(100.f, 100.f, 100.f);
	pSkyBox->Transform()->SetRelativeRot(Vec3(0.f, XM_PI / 2.f, 0.f));

	pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::CUBE);
	pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\SkyWater.dds"));
	//pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::SPHERE);
	//pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"Sky02"));

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

	CGameObject* pWall = new CGameObject;
	pWall->SetName(L"Wall");
	pWall->AddComponent(new CTransform);
	pWall->AddComponent(new CCollider3D);

	pWall->Transform()->SetRelativeScale(8000.f, 10.f, 8000.f);
	pWall->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pWall->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	pWall->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	pWall->Collider3D()->SetDebugShape(true);

	SpawnGameObject(pWall, Vec3(4000.f, 300.f, 4000.f), (int)LAYER::WALL);

	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pPlayer = nullptr;
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowPlayer.fbx");
	pPlayer = pMeshData->Instantiate();
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CPlayerScript);
	pPlayer->AddComponent(new CStateScript);
	pPlayer->AddComponent(new CCollider3D);
	pPlayer->AddComponent(new CRigidbody);
	
	pPlayer->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	pPlayer->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	
	pPlayer->MeshRender()->SetDynamicShadow(true);
	pPlayer->MeshRender()->SetFrustumCheck(false);
	
	pPlayer->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pPlayer->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 3.f));
	pPlayer->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 1.f));
	
	pPlayer->Rigidbody()->SetGravity(true);
	Stat PlayerStat;
	PlayerStat.Attack = 50.f;
	PlayerStat.Attack_Speed = 1.f;
	PlayerStat.HP = 4;
	PlayerStat.Speed = 1000.f;
	pPlayer->GetScript<CStateScript>()->SetStat(PlayerStat);
	
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

	
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\castle.fbx");
	CGameObject* pMonster = pMeshData->Instantiate();
	pMonster->SetName(L"Map");
	pMonster->MeshRender()->SetDynamicShadow(true);
	pMonster->MeshRender()->SetFrustumCheck(false);
	
	SpawnGameObject(pMonster, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\ARROW.fbx");
	//CGameObject* pObject = pMeshData->Instantiate();
	//pObject->SetName(L"arrow");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CRigidbody);
	//pObject->AddComponent(new CMagic_ArrowScript);
	//
	//pObject->Transform()->SetRelativeRot(XM_PI / 2.f, 0.f, XM_PI * 1.5f);
	//
	//pObject->Rigidbody()->SetFriction(1.f);
	//pObject->Rigidbody()->SetMass(1.f);
	//pObject->Rigidbody()->SetVelocityLimit(2000.f);
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));
	//
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::PLAYERPROJECTILE);

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bomb.fbx");
	CGameObject* pObject = pMeshData->Instantiate();
	pObject->SetName(L"Bomb");
	pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CRigidbody);
	pObject->AddComponent(new CMagic_BombScript);

	pObject->Transform()->SetRelativeRot(XM_PI / 2.f, 0.f, XM_PI * 1.5f);

	pObject->Rigidbody()->SetFriction(1.f);
	pObject->Rigidbody()->SetMass(1.f);
	pObject->Rigidbody()->SetVelocityLimit(2000.f);
	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));

	pObject->MeshRender()->SetDynamicShadow(true);
	pObject->MeshRender()->SetFrustumCheck(false);

	SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::PLAYERPROJECTILE);

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Fire.fbx");
	//CGameObject* pObject = pMeshData->Instantiate();
	//pObject->SetName(L"arrow");
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CRigidbody);
	//pObject->AddComponent(new CMagic_ArrowScript);
	//
	//pObject->Transform()->SetRelativeRot(XM_PI / 2.f, 0.f, XM_PI * 1.5f);
	//
	//pObject->Rigidbody()->SetFriction(1.f);
	//pObject->Rigidbody()->SetMass(1.f);
	//pObject->Rigidbody()->SetVelocityLimit(2000.f);
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetOffsetScale(Vec3(30.f, 30.f, 30.f));
	//
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pObject, Vec3(200.f, 200.f, 200.f), (int)LAYER::PLAYERPROJECTILE);

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Grunt.fbx");
	//CGameObject* pMonster = pMeshData->Instantiate();
	//pMonster->SetName(L"Monster");
	////pMonster->AddComponent(new CMonsterScript);
	////pMonster->AddComponent(new CStateScript);
	//pMonster->MeshRender()->SetDynamicShadow(true);
	//pMonster->MeshRender()->SetFrustumCheck(false);
	//
	//SpawnGameObject(pMonster, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);

	// ============
	// FBX Loading
	// ============	
	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bow.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Bow");
		pObj->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		pObj->Transform()->SetRelativeRot(XM_PI / 2.f, 0.f, XM_PI * 1.5f);
		pObj->Transform()->SetRelativePos(-0.3f, 1.f, 1.5f);
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);
		pPlayer->AddChild(pObj);

		//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\GrimKnight.fbx");
		//pObj = pMeshData->Instantiate();
		//pObj->SetName(L"GrimKnight");
		//pObj->MeshRender()->SetDynamicShadow(true);
		//pObj->MeshRender()->SetFrustumCheck(false);
		////
		//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), (int)LAYER::MONSTER);
	}
	
	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::WALL));
}
