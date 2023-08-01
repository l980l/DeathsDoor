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

#include <Script\CLurkerScript.h>
#include <Script\CBazookaScript.h>
#include <Script\CGruntScript.h>
#include <Script\CCrowBossScript.h>
#include <Script\CWaterCameraScript.h>

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
	//pSkyBox->SkyBox()->SetType(SKYBOX_TYPE::SPHERE);
	//pSkyBox->SkyBox()->SetSkyTexture(CResMgr::GetInst()->FindRes<CTexture>(L"Sky02"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);


	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* pPlayer = nullptr;
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowPlayer.fbx");
	pPlayer = pMeshData->Instantiate();
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CStateScript);
	pPlayer->AddComponent(new CCollider3D);

	pPlayer->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	pPlayer->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	pPlayer->MeshRender()->SetDynamicShadow(true);
	pPlayer->MeshRender()->SetFrustumCheck(false);

	pPlayer->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pPlayer->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 3.f));
	pPlayer->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 1.f));

	SpawnGameObject(pPlayer, Vec3(0.f, 500.f, 0.f), (int)LAYER::PLAYER);


	// 럴커
	CGameObject* pLurker = nullptr;
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Lurker.fbx");
	pLurker = pMeshData->Instantiate();
	pLurker->SetName(L"Lurker");
	pLurker->AddComponent(new CLurkerScript);
	pLurker->AddComponent(new CStateScript);
	pLurker->AddComponent(new CCollider3D);
	pLurker->AddComponent(new CRigidbody);

	pLurker->Transform()->SetRelativeScale(Vec3(0.5f, 0.5f, 0.5f));
	pLurker->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	pLurker->MeshRender()->SetDynamicShadow(true);
	pLurker->MeshRender()->SetFrustumCheck(false);

	pLurker->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pLurker->Collider3D()->SetOffsetScale(Vec3(320.f, 320.f, 220.f));
	pLurker->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 120.f));

	SpawnGameObject(pLurker, Vec3(100.f, 500.f, 1000.f), (int)LAYER::MONSTER);


	// 바주카
	CGameObject* pBazooka = nullptr;
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bazooka.fbx");
	pBazooka = pMeshData->Instantiate();
	pBazooka->SetName(L"Bazooka");
	pBazooka->AddComponent(new CBazookaScript);
	pBazooka->AddComponent(new CStateScript);
	pBazooka->AddComponent(new CCollider3D);
	pBazooka->AddComponent(new CRigidbody);

	pBazooka->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	pBazooka->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	pBazooka->MeshRender()->SetDynamicShadow(true);
	pBazooka->MeshRender()->SetFrustumCheck(false);

	pBazooka->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pBazooka->Collider3D()->SetOffsetScale(Vec3(400.f, 400.f, 540.f));
	pBazooka->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 300.f));

	SpawnGameObject(pBazooka, Vec3(700.f, 500.f, 1000.f), (int)LAYER::MONSTER);

	// 그런트
	CGameObject* pGrunt = nullptr;
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Grunt.fbx");
	pGrunt = pMeshData->Instantiate();
	pGrunt->SetName(L"Grunt");
	pGrunt->AddComponent(new CGruntScript);
	pGrunt->AddComponent(new CStateScript);
	pGrunt->AddComponent(new CCollider3D);
	pGrunt->AddComponent(new CRigidbody);

	pGrunt->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	pGrunt->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	pGrunt->MeshRender()->SetDynamicShadow(true);
	pGrunt->MeshRender()->SetFrustumCheck(false);

	pGrunt->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pGrunt->Collider3D()->SetOffsetScale(Vec3(220.f, 220.f, 320.f));
	pGrunt->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 200.f));

	SpawnGameObject(pGrunt, Vec3(400.f, 500.f, 1000.f), (int)LAYER::MONSTER);

	// Wind 
	CGameObject* pWind = new CGameObject;
	pWind->SetName(L"Wind");
	pWind->AddComponent(new CTransform);
	pWind->AddComponent(new CMeshRender);
	pWind->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pWind->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"WindMtrl"), 0);

	SpawnGameObject(pWind, Vec3(400.f, 500.f, 1000.f), (int)LAYER::DEFAULT);

	// Water 
	CGameObject* pWater = new CGameObject;
	pWater->SetName(L"Water");
	pWater->AddComponent(new CTransform);
	pWater->AddComponent(new CMeshRender);
	pWater->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pWater->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"WaterMtrl"), 0);
	pWater->Transform()->SetRelativeScale(8000.f, 8000.f, 8000.f);
	pWater->MeshRender()->SetFrustumCheck(false);

	SpawnGameObject(pWater, Vec3(4000.f, 520, 4000.f), (int)LAYER::DEFAULT);

	// Water Camera Object 생성
	CGameObject* pWaterCam = new CGameObject;
	pWaterCam->SetName(L"WaterCamera");

	pWaterCam->AddComponent(new CTransform);
	pWaterCam->AddComponent(new CCamera);
	pWaterCam->AddComponent(new CWaterCameraScript);

	pWaterCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pWaterCam->Camera()->SetCameraIndex(1);		 
	pWaterCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pWaterCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.
	pWaterCam->Camera()->SetWaterCamera(true);

	SpawnGameObject(pWaterCam, Vec3(0.f, 0.f, 0.f), 10);

	// 바닥
	CGameObject* pWall = new CGameObject;
	pWall->SetName(L"Wall");
	pWall->AddComponent(new CTransform);
	pWall->AddComponent(new CCollider3D);

	pWall->Transform()->SetRelativeScale(8000.f, 10.f, 8000.f);
	pWall->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::CUBE);
	pWall->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	pWall->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	pWall->Collider3D()->SetDebugShape(true);

	SpawnGameObject(pWall, Vec3(4000.f, 520, 4000.f), (int)LAYER::WALL);

	// 맵
	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\castle.fbx");
	CGameObject* pMonster = pMeshData->Instantiate();
	pMonster->SetName(L"Map");
	pMonster->MeshRender()->SetDynamicShadow(true);
	pMonster->MeshRender()->SetFrustumCheck(false);

	SpawnGameObject(pMonster, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);


	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTERPROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::MONSTER, (int)LAYER::WALL);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::WALL));
}
