#include "pch.h"
#include "CEnergyIconScript.h"
#include "CStateScript.h"
#include "CPlayerScript.h"

CEnergyIconScript::CEnergyIconScript() :
	CScript(SCRIPT_TYPE::ENERGYICONSCRIPT)
{
}

CEnergyIconScript::~CEnergyIconScript()
{
}

void CEnergyIconScript::begin()
{
	// µ¿Àû ÀçÁú »ý¼º.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-465.f, 319.f, 0.f));
	Transform()->SetRelativeScale(Vec3(154.f, 43.f, 0.f));
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EGempty.png", L"texture\\HUD\\EGempty.png", 0));

	
}

void CEnergyIconScript::tick()
{
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		Transform()->SetRelativePos(Vec3(-1000.f, 0.f, 0.f));
	}
	else
	{
		Transform()->SetRelativePos(Vec3(-465.f, 319.f, 0.f));
	}

	Stat playerStatus = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CStateScript>()->GetStat();
	int energy = playerStatus.Energy;
	CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
	UINT magicType = pScript->GetUseMagic();
	if (energy == 4 && magicType == (UINT)PLAYER_MAGIC::HOOK)//´Ù »¡°­
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG4r0w.png", L"texture\\HUD\\EG4r0w.png", 0));
	}
	else if (energy == 4 && magicType == (UINT)PLAYER_MAGIC::BOMB)//2°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG2r2w.png", L"texture\\HUD\\EG2r2w.png", 0));
	}
	else if (energy == 4 && magicType != (UINT)PLAYER_MAGIC::BOMB && magicType != (UINT)PLAYER_MAGIC::HOOK)// 1°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG3r1w.png", L"texture\\HUD\\EG3r1w.png", 0));
	}
	else if (energy == 3 && magicType == (UINT)PLAYER_MAGIC::HOOK)//´Ù »¡°­
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG3r0w.png", L"texture\\HUD\\EG3r0w.png", 0));
	}
	else if (energy == 3 && magicType == (UINT)PLAYER_MAGIC::BOMB)//2°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG1r2w.png", L"texture\\HUD\\EG1r2w.png", 0));
	}
	else if (energy == 3 && magicType != (UINT)PLAYER_MAGIC::BOMB && magicType != (UINT)PLAYER_MAGIC::HOOK)// 1°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG2r1w.png", L"texture\\HUD\\EG2r1w.png", 0));
	}
	else if (energy == 2 && magicType == (UINT)PLAYER_MAGIC::HOOK)//´Ù »¡°­
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG2r0w.png", L"texture\\HUD\\EG2r0w.png", 0));
	}
	else if (energy == 2 && magicType == (UINT)PLAYER_MAGIC::BOMB)//2°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG0r2w.png", L"texture\\HUD\\EG0r2w.png", 0));
	}
	else if (energy == 2 && magicType != (UINT)PLAYER_MAGIC::BOMB && magicType != (UINT)PLAYER_MAGIC::HOOK)// 1°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG1r1w.png", L"texture\\HUD\\EG1r1w.png", 0));
	}
	else if (energy == 1 && magicType == (UINT)PLAYER_MAGIC::HOOK)//´Ù »¡°­
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG1r0w.png", L"texture\\HUD\\EG1r0w.png", 0));
	}
	else if (energy == 1 && magicType == (UINT)PLAYER_MAGIC::BOMB)//2°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG1r0w.png", L"texture\\HUD\\EG1r0w.png", 0));
	}
	else if (energy == 1 && magicType != (UINT)PLAYER_MAGIC::BOMB && magicType != (UINT)PLAYER_MAGIC::HOOK)// 1°³¸¸ Èò»ö
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EG0r1w.png", L"texture\\HUD\\EG0r1w.png", 0));
	}
	else if (energy == 0)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\EGempty.png", L"texture\\HUD\\EGempty.png", 0));
	}
}
