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
#include <Script/CMainLightScript.h>
#include <Script/CWaterCameraScript.h>
#include <Script/CCrowBossScript.h>
#include <Script/CSlashScript.h>
#include <Script/CMonsterDetectRangeScript.h>
#include <Script/CBossChainScript.h>
#include <Script/CWaterScript.h>
#include <Script/CLadderScript.h>
#include <Script\CArrowIconScript.h>
#include <Script\CFireIconScript.h>
#include <Script\CBombIconScript.h>
#include <Script\CHookIconScript.h>
#include <Script\CHPIconScript.h>
#include <Script\CEnergyIconScript.h>
#include <Script/CSoundScript.h>
#include <Script/CLevelChangeDoorScript.h>
#include <Script/CCursorScript.h>
#include <Engine/CEventMgr.h>

#include <Engine/CDetourMgr.h>
#include <Engine/CPhysXMgr.h>

#include "CLevelSaveLoad.h"


void CreateTestLevel()
{
	Stat PlayerStat;
	PlayerStat.Attack = 50.f;
	PlayerStat.Attack_Speed = 0.4f;
	PlayerStat.HP = 4;
	PlayerStat.Speed = 150.f;
	PlayerStat.Spell_Power = 40.f;
	PlayerStat.Energy = 4;
	PlayerStat.Max_Energy = 4;

	g_tPlayerStat = PlayerStat;

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, (int)LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::GROUND));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::FALLAREA));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::LADDER));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::MONSTERPROJECTILE));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::ANCHOR));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYERPROJECTILE, ((int)LAYER::MONSTER));
	CCollisionMgr::GetInst()->LayerCheck((int)LAYER::PLAYER, ((int)LAYER::LEVELCHANGEDOOR));

	//CLevel* NewLevel = CLevelSaveLoad::Stop(L"Level\\Ice_Boss.lv", LEVEL_STATE::STOP);
	//NewLevel->SetName(L"Ice_Boss");
	//NewLevel->SetLevelType((int)LEVEL_TYPE::ICE_BOSS);
	//tEvent evn = {};
	//evn.Type = EVENT_TYPE::LEVEL_CHANGE;
	//evn.wParam = (DWORD_PTR)NewLevel;
	//evn.lParam = (DWORD_PTR)NewLevel->GetLevelType();
	//CEventMgr::GetInst()->AddEvent(evn);
	//
	//return;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);
	pCurLevel->SetLevelType((int)LEVEL_TYPE::CASTLE_FIELD);
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

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), (int)LAYER::MAINCAMERA);

	CGameObject* pSubCam = new CGameObject;
	pSubCam->SetName(L"SubCamera");

	pSubCam->AddComponent(new CTransform);
	pSubCam->AddComponent(new CCamera);
	pSubCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pSubCam->Camera()->SetCameraIndex(2);
	pSubCam->Camera()->SetLayerMaskAll(false);
	pSubCam->Camera()->SetLayerMask(31, true);// UI Layer 는 렌더링하지 않는다.

	SpawnGameObject(pSubCam, Vec3(0.f, 0.f, 0.f), (int)LAYER::SUBCAMERA);

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

	pPlayer->GetScript<CStateScript>()->SetStat(PlayerStat);
	CPhysXMgr::GetInst()->CreateSphere(Vec3(2400, 2000.f, 2400), 20.f, pPlayer);
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


	//pObject = new CGameObject;
	//pObject->SetName(L"MouseAim");
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	//pObject->AddComponent(new CCollider3D);
	//pObject->AddComponent(new CLevelChangeDoorScript);
	//
	//pObject->Transform()->SetRelativeScale(Vec3(120.f));
	//pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	//pObject->Collider3D()->SetAbsolute(true);
	//pObject->Collider3D()->SetOffsetScale(Vec3(150.f));
	//pObject->GetScript<CLevelChangeDoorScript>()->SetLevelType(LEVEL_TYPE::CASTLE_FIELD);
	//
	//SpawnGameObject(pObject, Vec3(2500.f, 1000.f, 2500.f), (int)LAYER::DEFAULT);

	pObject = new CGameObject;
	pObject->SetName(L"Anchor");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider3D);

	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetAbsolute(true);
	pObject->Collider3D()->SetDebugShape(true);
	pObject->Collider3D()->SetOffsetScale(Vec3(300.f));

	SpawnGameObject(pObject, Vec3(3500.f, 0.f, 3500.f), (int)LAYER::ANCHOR);

	pObject = new CGameObject;
	pObject->SetName(L"Ladder");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CLadderScript);

	pObject->Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);

	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetAbsolute(true);
	pObject->Collider3D()->SetDebugShape(true);
	pObject->Collider3D()->SetOffsetScale(Vec3(300.f));

	pObject->GetScript<CLadderScript>()->SetHeight(500.f);

	SpawnGameObject(pObject, Vec3(2000.f, 550.f, 3000.f), (int)LAYER::LADDER);

	//==========================
	// UI
	//==========================

	CGameObject* pArrowIcon = new CGameObject;
	pArrowIcon->SetName(L"ArrowIcon");
	pArrowIcon->AddComponent(new CTransform);
	pArrowIcon->AddComponent(new CMeshRender);
	pArrowIcon->AddComponent(new CArrowIconScript);
	pArrowIcon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pArrowIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
	SpawnGameObject(pArrowIcon, Vec3(0.f, 0.f, 0.f), (int)LAYER::UI);

	CGameObject* pFireIcon = new CGameObject;
	pFireIcon->SetName(L"FireIcon");
	pFireIcon->AddComponent(new CTransform);
	pFireIcon->AddComponent(new CMeshRender);
	pFireIcon->AddComponent(new CFireIconScript);
	pFireIcon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pFireIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
	SpawnGameObject(pFireIcon, Vec3(0.f, 0.f, 0.f), (int)LAYER::UI);

	CGameObject* pBombIcon = new CGameObject;
	pBombIcon->SetName(L"BombIcon");
	pBombIcon->AddComponent(new CTransform);
	pBombIcon->AddComponent(new CMeshRender);
	pBombIcon->AddComponent(new CBombIconScript);
	pBombIcon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pBombIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
	SpawnGameObject(pBombIcon, Vec3(0.f, 0.f, 0.f), (int)LAYER::UI);

	CGameObject* pHookIcon = new CGameObject;
	pHookIcon->SetName(L"HookIcon");
	pHookIcon->AddComponent(new CTransform);
	pHookIcon->AddComponent(new CMeshRender);
	pHookIcon->AddComponent(new CHookIconScript);
	pHookIcon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pHookIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
	SpawnGameObject(pHookIcon, Vec3(0.f, 0.f, 0.f), (int)LAYER::UI);

	CGameObject* pHPIcon = new CGameObject;
	pHPIcon->SetName(L"HPIcon");
	pHPIcon->AddComponent(new CTransform);
	pHPIcon->AddComponent(new CMeshRender);
	pHPIcon->AddComponent(new CHPIconScript);
	pHPIcon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pHPIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
	SpawnGameObject(pHPIcon, Vec3(0.f, 0.f, 0.f), (int)LAYER::UI);

	CGameObject* pEnergyIcon = new CGameObject;
	pEnergyIcon->SetName(L"EnergyIcon");
	pEnergyIcon->AddComponent(new CTransform);
	pEnergyIcon->AddComponent(new CMeshRender);
	pEnergyIcon->AddComponent(new CEnergyIconScript);
	pEnergyIcon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pEnergyIcon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
	SpawnGameObject(pEnergyIcon, Vec3(0.f, 0.f, 0.f), (int)LAYER::UI);


	CGameObject* pSoundMgr = new CGameObject;
	pSoundMgr->SetName(L"SoundUI");
	pSoundMgr->AddComponent(new CTransform);
	pSoundMgr->AddComponent(new CMeshRender);
	pSoundMgr->AddComponent(new CSoundScript);

	pSoundMgr->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pSoundMgr->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);

	SpawnGameObject(pSoundMgr, Vec3(0.f), (int)LAYER::DEFAULT);



	pObject = new CGameObject;
	pObject->SetName(L"Cursor");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CCursorScript);

	pObject->Transform()->SetRelativeScale(Vec3(70.f));
	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);

	SpawnGameObject(pObject, Vec3(0.f), (int)LAYER::UI);


	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\ShortcutDoor.fbx");
	CGameObject* pShortcutDoor = pMeshData->Instantiate();
	pShortcutDoor->SetName(L"ShortcutDoor");
	pShortcutDoor->AddComponent(new CCollider3D);
	pShortcutDoor->AddComponent(new CLevelChangeDoorScript);

	pShortcutDoor->Transform()->SetRelativeScale(Vec3(120.f));
	pShortcutDoor->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pShortcutDoor->Collider3D()->SetAbsolute(true);
	pShortcutDoor->Collider3D()->SetOffsetScale(Vec3(150.f));
	pShortcutDoor->GetScript<CLevelChangeDoorScript>()->SetLevelType((int)LEVEL_TYPE::CASTLE_FIELD);

	SpawnGameObject(pShortcutDoor, Vec3(2500.f, 1000.f, 2500.f), (int)LAYER::LEVELCHANGEDOOR);

	// ======================
	// Map
	// ======================

	//CDetourMgr::GetInst()->ChangeLevel(LEVEL_TYPE::CASTLE_FIELD);
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\PhysXmap\\Castle_Simple.fbx");
	//pObject = pMeshData->Instantiate();
	//CPhysXMgr::GetInst()->ConvertStatic(Vec3(0.f, 0.f, 0.f), pObject);
	//
	//delete pObject;
	//
	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Map\\Castle.fbx");
	//pObject = pMeshData->Instantiate();
	//pObject->SetName(L"Map");
	//pObject->MeshRender()->SetDynamicShadow(true);
	//pObject->MeshRender()->SetFrustumCheck(false);
	//SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), (int)LAYER::DEFAULT);

	CGameObject* pFloor = new CGameObject;
	pFloor->AddComponent(new CTransform);
	pFloor->AddComponent(new CMeshRender);

	pFloor->Transform()->SetRelativeScale(50000.f, 10.f, 50000.f);
	pFloor->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
	pFloor->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);
	pFloor->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"textur\CrowBossMapFloor.png"));
	pFloor->GetRenderComponent()->SetFrustumCheck(false);
	pFloor->GetRenderComponent()->SetDynamicShadow(true);
	SpawnGameObject(pFloor, Vec3(0.f), (int)LAYER::GROUND);
	CPhysXMgr::GetInst()->CreatePlane(Vec4(0.f, 1.f, 0.f, 0.f));

	CLevelSaveLoad::SpawnPrefab(L"prefab\\Knight.prefab", (int)LAYER::MONSTER, Vec3(0.f));


}
