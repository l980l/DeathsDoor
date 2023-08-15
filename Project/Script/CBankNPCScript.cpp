#include "pch.h"
#include "CBankNPCScript.h"
#include "CLevelSaveLoadInScript.h"

CBankNPCScript::CBankNPCScript()		:
	CScript(SCRIPT_TYPE::BANKNPCSCRIPT)
{
}

CBankNPCScript::~CBankNPCScript()
{
}

void CBankNPCScript::begin()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}
}

void CBankNPCScript::tick()
{
}

void CBankNPCScript::BeginOverlap(CCollider3D* _Other)
{
	CLevelSaveLoadInScript script;
	if (!CLevelMgr::GetInst()->FindObjectByName(L"Talk"))
	{
		talksign = script.SpawnandReturnPrefab(L"prefab\\Talk.prefab", 31, Vec3(0.f, 0.f, 0.f));
		talksign->Transform()->SetRelativeScale(81.f, 38.f, 1.f);
		int mtrlCount = talksign->MeshRender()->GetMtrlCount();
		for (int i = 0; i < mtrlCount; ++i)
		{
			talksign->MeshRender()->GetDynamicMaterial(i);
		}
	}
}

void CBankNPCScript::OnOverlap(CCollider3D* _Other)
{
	CLevelSaveLoadInScript script;
	if (L"Player" == _Other->GetOwner()->GetName())
	{
		
		if (KEY_TAP(KEY::E)&& LEVEL_STATE::PLAY == CLevelMgr::GetInst()->GetCurLevel()->GetState())
		{
			talksign->SetLifeSpan(0.f);

			//상점 Frame & Upgrade 스텟 spawn
			
			if (!CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
			{
				CGameObject* BankUIFrame = script.SpawnandReturnPrefab(L"prefab\\BankUIFrame.prefab", 31, Vec3(0.f,0.f,100.f));
			}
			if (!CLevelMgr::GetInst()->FindObjectByName(L"BankUIUpgrade"))
			{
				CGameObject* BankUIUpgrade = script.SpawnandReturnPrefab(L"prefab\\BankUIUpgrade.prefab", 31, Vec3(0.f, 0.f, 0.f));
			}

			//Main Cam 각도 변경
			CGameObject* mainCam = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");
			mainCam->Transform()->SetRelativePos(Vec3(1698.f, 1443.f, 3470.f));
			Vec3 rot = (Vec3(8.f, -62.f, 0.f) / 180.f) * XM_PI;
			mainCam->Transform()->SetRelativeRot(rot);
		}
		if (KEY_TAP(KEY::ESC))
		{
			CGameObject* UIFrame = CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame");
			UIFrame->SetLifeSpan(0.f);
			CGameObject* UIUpgrade = CLevelMgr::GetInst()->FindObjectByName(L"BankUIUpgrade");
			UIUpgrade->SetLifeSpan(0.f);
		}
	}

}

void CBankNPCScript::EndOverlap(CCollider3D* _Other)
{
	//CGameObject* Message = CLevelMgr::GetInst()->FindObjectByName(L"Talk");
	//Message->SetLifeSpan(0.f);
}
