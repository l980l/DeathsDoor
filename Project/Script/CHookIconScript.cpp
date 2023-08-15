#include "pch.h"
#include "CHookIconScript.h"
#include "CPlayerScript.h"

CHookIconScript::CHookIconScript() :
	CScript(SCRIPT_TYPE::HOOKICONSCRIPT)
{
}

CHookIconScript::~CHookIconScript()
{
}

void CHookIconScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-651.f, 208.f, 0.f));
	Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\HookDA.png", L"texture\\HUD\\HookDA.png", 0));
}

void CHookIconScript::tick()
{
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		Transform()->SetRelativePos(Vec3(-1000.f, 0.f, 0.f));
	}
	else
	{
		CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
		UINT magicState = pScript->GetUseMagic();
		if (magicState == (UINT)PLAYER_MAGIC::HOOK)
		{
			Transform()->SetRelativePos(Vec3(-651.f, 199.f, 0.f));
			Transform()->SetRelativeScale(Vec3(100, 116.f, 0.f));

			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\HookActive.png"));
		}
		else
		{
			Transform()->SetRelativePos(Vec3(-651.f, 208.f, 0.f));
			Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\HookDA.png"));
		}
	}

	
}
