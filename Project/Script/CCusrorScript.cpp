#include "pch.h"
#include "CCusrorScript.h"

CCusrorScript::CCusrorScript()
	: CScript((UINT)CURSORSCRIPT)
{
}

CCusrorScript::~CCusrorScript()
{
}

void CCusrorScript::begin()
{
	MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"AIM"));
	MeshRender()->GetDynamicMaterial();
}

void CCusrorScript::tick()
{
	Vec3 MousePos = CRenderMgr::GetInst()->GetRay();
	Vec3 MainCamPos = CRenderMgr::GetInst()->GetMainCam()->GetOwner()->Transform()->GetWorldPos();
	Transform()->SetRelativePos(MousePos.x - MainCamPos.x, MousePos.y - MainCamPos.y, 1.f);
}
