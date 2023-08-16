#include "pch.h"
#include "CArrowIconScript.h"
#include "CPlayerScript.h"
#include "CLevelSaveLoadinScript.h"

CArrowIconScript::CArrowIconScript() :
	CScript(SCRIPT_TYPE::ARROWICONSCRIPT)
{
}

CArrowIconScript::~CArrowIconScript()
{
}

void CArrowIconScript::begin()
{
	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-652.f, 323.f, 0.f));
	Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\ArrowDA.png", L"texture\\HUD\\ArrowDA.png", 0));
}

void CArrowIconScript::tick()
{
	if (CLevelMgr::GetInst()->FindObjectByName(L"BankUIFrame"))
	{
		Transform()->SetRelativePos(Vec3(-1000.f, 0.f, 0.f));
	}
	else
	{
		CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
		UINT magicState = pScript->GetUseMagic();
		if (magicState == (UINT)PLAYER_MAGIC::ARROW)
		{
			Transform()->SetRelativePos(Vec3(-652.f, 331.f, 0.f));
			Transform()->SetRelativeScale(Vec3(100.f, 116.f, 0.f));

			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\ArrowActive.png", L"texture\\HUD\\ArrowActive.png", 0));
		}
		else
		{
			Transform()->SetRelativePos(Vec3(-652.f, 323.f, 0.f));
			Transform()->SetRelativeScale(Vec3(100.f, 100.f, 0.f));
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\ArrowDA.png", L"texture\\HUD\\ArrowDA.png", 0));
		}
	}
	
}
