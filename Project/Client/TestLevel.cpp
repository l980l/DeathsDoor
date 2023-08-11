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
#include <Script/CKnightScript.h>
#include <Script/CGrimKnightScript.h>
#include <Engine/CSound.h>
#include "CLevelSaveLoad.h"


void CreateTestLevel()
{
	CLevelSaveLoad script;
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);
	CLevel* NewLevel = CLevelSaveLoad::Stop(L"Level\\Castle.lv", LEVEL_STATE::STOP);
	NewLevel->SetName(L"Castle");

	tEvent evn = {};
	evn.Type = EVENT_TYPE::LEVEL_CHANGE;
	evn.wParam = (DWORD_PTR)NewLevel;
	CEventMgr::GetInst()->AddEvent(evn);


	/*Ptr<CSound> CrowBossBGM = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BGM\\DeathsDoorPiano.mp3");
	CrowBossBGM->PlayBGM(0, 0.5f);

	Ptr<CSound> BatAttack = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\Monster\\Bat\\BatAttack.ogg");
	BatAttack->PlaySFX(0, 0.5f);*/

	//pSound->g_pFMOD->createSound("testsound",FMOD_MODE::)
	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::GROUND));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::FALLAREA));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::LADDER));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::ITEM));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::ANCHOR));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::MONSTER));

	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pPlayer = nullptr;
	CGameObject* pObject = nullptr;
	CGameObject* Knight = nullptr;
	CGameObject* GKnight = nullptr;

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Fence.fbx");
	//GKnight = pMeshData->Instantiate();
	//GKnight->SetName(L"Fence");
	//GKnight->AddComponent(new CFenseScript);
	//GKnight->AddComponent(new CCollider3D);
	////GKnight->AddComponent(new CRigidbody);

	//GKnight->Transform()->SetRelativeScale(Vec3(0.2f, 0.2f, 0.2f));
	//GKnight->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	//GKnight->MeshRender()->SetDynamicShadow(true);
	//GKnight->MeshRender()->SetFrustumCheck(false);

	//GKnight->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	//GKnight->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	//GKnight->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 1.f));
	//
	//SpawnGameObject(GKnight, Vec3(2500.f, 500.f, 2500.f), (int)LAYER::ITEM);

	CGameObject* pGhost = new CGameObject;
	pGhost->SetName(L"Ghost");

	pGhost->AddComponent(new CTransform);
	pGhost->AddComponent(new CCollider3D);
	pGhost->AddComponent(new CMeshRender);

	pGhost->Transform()->SetRelativeScale(100.f, 100.f, 100.f);
	pGhost->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	pGhost->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);
	int a = 1;
	pGhost->MeshRender()->GetMaterial(0)->SetScalarParam(INT_0, &a);
	//pGhost->MeshRender()->GetMaterial(0)->SetScalarParam(VEC4_0, Vec4(0.1f,0.f,0.5f,1.f));
	pGhost->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\GhostGreen.png"));
	SpawnGameObject(pGhost, Vec3(2500.f, 800.f, 3000.f), 0);


	return;
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


	

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Knight.fbx");
	//Knight = pMeshData->Instantiate();
	//Knight->SetName(L"Knight");
	//Knight->AddComponent(new CStateScript);
	//Knight->AddComponent(new CCollider3D);
	//Knight->AddComponent(new CRigidbody);
	//Knight->AddComponent(new CKnightScript);
	//Knight->Transform()->SetRelativeScale(Vec3(0.2f, 0.2f, 0.2f));
	//Knight->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	//Knight->MeshRender()->SetDynamicShadow(true);
	//Knight->MeshRender()->SetFrustumCheck(false);

	//Knight->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	//Knight->Collider3D()->SetOffsetScale(Vec3(1000.f, 1000.f, 1000.f));
	//Knight->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 200.f));
	//CPhysXMgr::GetInst()->CreateSphere(Vec3(1500.f, 500.f, 3400.f), 20.f, Knight);
	//SpawnGameObject(Knight, Vec3(1500.f, 500.f, 3400.f), (int)LAYER::MONSTER);
	//CGameObject* range = script.SpawnandReturnPrefab(L"prefab\\DetectRange.prefab", 6, Vec3(0.f, 0.f, 0.f));

	//range->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);

	

	//==================
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
	
	script.SpawnPrefab(L"prefab\\Trap1.prefab", 8, Vec3(2278.f, 500.f, 2414.f));

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::GROUND));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::FALLAREA));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::LADDER));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::ITEM));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::ANCHOR));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::MONSTER));
}
