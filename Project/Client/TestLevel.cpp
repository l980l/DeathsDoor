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
#include <Script/CStateScript.h>
#include <Script\CMonsterScript.h>
#include <Script/CCameraMoveScript.h>

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
	CGameObject* pDecal = new CGameObject;
	pDecal->SetName(L"Decal");
	pDecal->AddComponent(new CTransform);
	pDecal->AddComponent(new CDecal);

	pDecal->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 200.f));
	pDecal->Decal()->SetOutputTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\MagicCircle.png"));
	pDecal->Decal()->SetAsLight(false);

	SpawnGameObject(pDecal, Vec3(0.f, 200.f, 0.f), (int)LAYER::DEFAULT);


	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CRigidbody);
	pObject->AddComponent(new CPlayerScript);
	pObject->AddComponent(new CStateScript);

	pObject->Transform()->SetRelativeScale(Vec3(500.f, 500.f, 500.f));

	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));
	pObject->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));

	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);
	//pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"TILE_03"));
	//pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"TILE_03_N"));
	pObject->MeshRender()->SetDynamicShadow(true);

	SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::PLAYER);

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Banker.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Banker");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);
		
		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bat.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Bat");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}
	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Bazooka.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Bazooka");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}
	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowBoss.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"CrowBoss");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}
	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowHead.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"CrowHead");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}
	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowSword.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"CrowSword");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\CrowPlayer.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"CrowPlayer");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\GrimKnight.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"GrimKnight");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Knight.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Knight");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Grunt.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Grunt");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	{
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Lurker.fbx");
		pObj = pMeshData->Instantiate();
		pObj->SetName(L"Lurker");
		pObj->MeshRender()->SetDynamicShadow(true);
		pObj->MeshRender()->SetFrustumCheck(false);

		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	// ============
	// FBX Loading
	// ============	
	{
		//Ptr<CMeshData> pMeshData = nullptr;
		//CGameObject* pObj = nullptr;
		//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\map\\castle\\Rock.fbx");
		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\house.mdat");
		//pObj = pMeshData->Instantiate();;
		//pObj->SetName(L"House");

		//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Ice_Field.fbx");
		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\Castle_Field.mdat");
		//pObj = pMeshData->Instantiate();
		//pObj->SetName(L"Hall");
		//pObj->AddComponent(new CMonsterScript);
		//pObj->MeshRender()->SetDynamicShadow(true);
		//pObj->MeshRender()->SetFrustumCheck(false);
		//
		//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");	
}
