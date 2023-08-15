#include "pch.h"
#include "CFireIconScript.h"
#include "CPlayerScript.h"

CFireIconScript::CFireIconScript() :
	CScript(SCRIPT_TYPE::FIREICONSCRIPT)
{
}

CFireIconScript::~CFireIconScript()
{
}

void CFireIconScript::begin()
{
	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-709.f, 265.f, 0.f));
	Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
	
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\FireDA.png", L"texture\\HUD\\FireDA.png", 0));
}

void CFireIconScript::tick()
{
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		Transform()->SetRelativePos(Vec3(-1000.f, 0.f, 0.f));
	}
	else
	{
		CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
		UINT magicState = pScript->GetUseMagic();
		if (magicState == (UINT)PLAYER_MAGIC::FIRE)
		{
			Transform()->SetRelativePos(Vec3(-717.f, 265.f, 0.f));
			Transform()->SetRelativeScale(Vec3(116, 100.f, 0.f));

			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\FireActive.png", L"texture\\HUD\\FireActive.png",0));
		}
		else
		{
			Transform()->SetRelativePos(Vec3(-709.f, 265.f, 0.f));
			Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\FireDA.png", L"texture\\HUD\\FireDA.png",0));
		}
	}

	
}
