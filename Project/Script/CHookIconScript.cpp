#include "pch.h"
#include "CHookIconScript.h"
#include "CPlayerScript.h"
#include "CLevelSaveLoadInScript.h"

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

	Transform()->SetRelativePos(Vec3(-1648.f, 654.f, 0.f));
	Transform()->SetRelativeScale(Vec3(231.f, 231.f, 0.f));
	Vec3 camRot = CLevelMgr::GetInst()->FindObjectByName(L"MainCam")->Transform()->GetRelativeRot();
	Vec3 rot = (camRot / 180.f) * XM_PI;
	Transform()->SetRelativeRot(rot);
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\HookDA.png"));
}

void CHookIconScript::tick()
{
	Vec3 camRot = CLevelMgr::GetInst()->FindObjectByName(L"MainCam")->Transform()->GetRelativeRot();
	Vec3 rot = (camRot / 180.f) * XM_PI;
	Transform()->SetRelativeRot(rot);

	CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
	UINT magicState = pScript->GetUseMagic();
	if (magicState == (UINT)PLAYER_MAGIC::HOOK)
	{
		Transform()->SetRelativePos(Vec3(-1648.f, 632.f, 0.f));
		Transform()->SetRelativeScale(Vec3(231, 276.f, 0.f));

		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\HookActive.png"));
	}
	else
	{
		Transform()->SetRelativePos(Vec3(-1648.f, 654.f, 0.f));
		Transform()->SetRelativeScale(Vec3(231.f, 231.f, 0.f));
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\HookDA.png"));
	}

	if (KEY_TAP(KEY::O))
	{
		CLevelSaveLoadInScript script;
		script.MoneyCount(600, CLevelMgr::GetInst()->FindObjectByName(L"MainCam"));
	}
}
