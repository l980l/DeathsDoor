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
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-1779.f, 785.f, 0.f));
	Transform()->SetRelativeScale(Vec3(231.f, 231.f, 0.f));
	Vec3 camRot = CLevelMgr::GetInst()->FindObjectByName(L"MainCam")->Transform()->GetRelativeRot();
	Vec3 rot = (camRot / 180.f) * XM_PI;
	Transform()->SetRelativeRot(rot);
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\FireDA.png"));
}

void CFireIconScript::tick()
{
	Vec3 camRot = CLevelMgr::GetInst()->FindObjectByName(L"MainCam")->Transform()->GetRelativeRot();
	Vec3 rot = (camRot / 180.f) * XM_PI;
	Transform()->SetRelativeRot(rot);

	CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
	UINT magicState = pScript->GetUseMagic();
	if (magicState == (UINT)PLAYER_MAGIC::FIRE)
	{
		Transform()->SetRelativePos(Vec3(-1791.f, 785.f, 0.f));
		Transform()->SetRelativeScale(Vec3(276, 231.f, 0.f));

		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\FireActive.png"));
	}
	else
	{
		Transform()->SetRelativePos(Vec3(-1779.f, 785.f, 0.f));
		Transform()->SetRelativeScale(Vec3(231.f, 231.f, 0.f));
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\FireDA.png"));
	}
}
