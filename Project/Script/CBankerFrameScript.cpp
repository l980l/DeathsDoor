#include "pch.h"
#include "CBankerFrameScript.h"
#include <Engine/CEventMgr.h>

CBankerFrameScript::CBankerFrameScript() :
	CScript(SCRIPT_TYPE::BANKERFRAMESCRIPT)
{
}

CBankerFrameScript::~CBankerFrameScript()
{
}

void CBankerFrameScript::begin()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	GetOwner()->Transform()->SetRelativeScale(Vec3(1913.f, 982.f, 1.f));
	Vec3 rot = (Vec3(0.f, -62.f, 0.f) / 180.f) * XM_PI;
	GetOwner()->Transform()->SetRelativeRot(rot);

	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\BankUI.png"));
}

void CBankerFrameScript::tick()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\BankUI.png"));

	if (KEY_TAP(KEY::ESC))
	{
		tEvent evn = {};
		evn.Type = EVENT_TYPE::DELETE_OBJECT;
		evn.wParam = (DWORD_PTR)this->GetOwner();
		CEventMgr::GetInst()->AddEvent(evn);
	}
}

void CBankerFrameScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBankerFrameScript::OnOverlap(CCollider3D* _Other)
{
}

void CBankerFrameScript::EndOverlap(CCollider3D* _Other)
{
}
