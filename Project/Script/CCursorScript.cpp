#include "pch.h"
#include "CCursorScript.h"
#include <Engine/CRenderMgr.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CCamera.h>

CCursorScript::CCursorScript()
	: CScript((UINT)CURSORSCRIPT)
{
	
}

CCursorScript::~CCursorScript()
{
}

void CCursorScript::begin()
{
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"AIM"));
	MeshRender()->GetDynamicMaterial(0);
}

void CCursorScript::tick()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	tRay tMainCamRay = CRenderMgr::GetInst()->GetMainCam()->GetRay();
	Vec3 vMainCamPos = CRenderMgr::GetInst()->GetMainCam()->GetOwner()->Transform()->GetWorldPos();
	float PlayerY = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player")->Transform()->GetWorldPos().y;
	Transform()->SetRelativePos(vMainCamPos.x + vMousePos.x, PlayerY, vMainCamPos.z + vMousePos.y);
	Transform()->SetRelativeRot(XM_PI / 2.f, tMainCamRay.vDir.y, 0.f);
}
