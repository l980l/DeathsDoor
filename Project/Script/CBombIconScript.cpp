#include "pch.h"
#include "CBombIconScript.h"
#include "CPlayerScript.h"

CBombIconScript::CBombIconScript() :
	CScript(SCRIPT_TYPE::BOMBICONSCRIPT)
{
}

CBombIconScript::~CBombIconScript()
{
}

void CBombIconScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-595.f, 265.f, 0.f));
	Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\BombDA.png"));
}

void CBombIconScript::tick()
{
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		Transform()->SetRelativePos(Vec3(-1000.f, 0.f, 0.f));
	}
	else
	{
		CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
		UINT magicState = pScript->GetUseMagic();
		if (magicState == (UINT)PLAYER_MAGIC::BOMB)
		{
			Transform()->SetRelativePos(Vec3(-587.f, 265.f, 0.f));
			Transform()->SetRelativeScale(Vec3(116.f, 100.f, 0.f));

			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\BombActive.png"));
		}
		else
		{
			Transform()->SetRelativePos(Vec3(-595.f, 265.f, 0.f));
			Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\BombDA.png"));
		}
	}

	
}
