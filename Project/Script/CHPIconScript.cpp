#include "pch.h"
#include "CHPIconScript.h"
#include "CStateScript.h"

CHPIconScript::CHPIconScript() :
	CScript(SCRIPT_TYPE::HPICONSCRIPT)
{
}

CHPIconScript::~CHPIconScript()
{
}

void CHPIconScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-444.f, 367.f, 0.f));
	Transform()->SetRelativeScale(Vec3(217.f, 41.f, 0.f));

	Stat playerStatus = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CStateScript>()->GetStat();
	int hp = playerStatus.HP;

	if (hp == 4)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_4.png", L"texture\\HUD\\HP_4.png", 0));
	}
	else if (hp == 3)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_3.png", L"texture\\HUD\\HP_3.png", 0));
	}
	else if (hp == 2)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_2.png", L"texture\\HUD\\HP_2.png", 0));
	}
	else if (hp == 1)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_1.png", L"texture\\HUD\\HP_1.png", 0));
	}
}

void CHPIconScript::tick()
{


	Stat playerStatus = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CStateScript>()->GetStat();
	int hp = playerStatus.HP;

	if (hp == 4)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_4.png", L"texture\\HUD\\HP_4.png", 0));
	}
	else if (hp == 3)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_3.png", L"texture\\HUD\\HP_3.png", 0));
	}
	else if (hp == 2)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_2.png", L"texture\\HUD\\HP_2.png", 0));
	}
	else if (hp == 1)
	{
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HP_1.png", L"texture\\HUD\\HP_1.png", 0));
	}
}
