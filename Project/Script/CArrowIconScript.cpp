#include "pch.h"
#include "CArrowIconScript.h"
#include "CPlayerScript.h"

CArrowIconScript::CArrowIconScript() :
	CScript(SCRIPT_TYPE::ARROWICONSCRIPT)
{
}

CArrowIconScript::~CArrowIconScript()
{
}

void CArrowIconScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	Transform()->SetRelativePos(Vec3(-1650.f, 915.f, 0.f));
	Transform()->SetRelativeScale(Vec3(231.f, 231.f, 0.f));
	Vec3 camRot = CLevelMgr::GetInst()->FindObjectByName(L"MainCam")->Transform()->GetRelativeRot();
	Vec3 rot = (camRot / 180.f) * XM_PI;
	Transform()->SetRelativeRot(rot);
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\ArrowDA.png"));
}

void CArrowIconScript::tick()
{
	Vec3 camRot = CLevelMgr::GetInst()->FindObjectByName(L"MainCam")->Transform()->GetRelativeRot();
	Vec3 rot = (camRot / 180.f) * XM_PI;
	Transform()->SetRelativeRot(rot);

	CPlayerScript* pScript = CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>();
	UINT magicState = pScript->GetUseMagic();
	if (magicState == (UINT)PLAYER_MAGIC::ARROW)
	{
		Transform()->SetRelativePos(Vec3(-1650.f, 937.f, 0.f));
		Transform()->SetRelativeScale(Vec3(231.f, 276.f, 0.f));
		
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\ArrowActive.png"));
	}
	else
	{
		Transform()->SetRelativePos(Vec3(-1650.f, 915.f, 0.f));
		Transform()->SetRelativeScale(Vec3(231.f, 231.f, 0.f));
		MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HUD\\ArrowDA.png"));
	}
}
