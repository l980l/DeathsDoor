#include "pch.h"
#include "CBankerFrameScript.h"
#include "CStateScript.h"
#include <Engine/CEventMgr.h>

CBankerFrameScript::CBankerFrameScript() :
	CScript(SCRIPT_TYPE::BANKERFRAMESCRIPT),
	m_count(0)
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

	GetOwner()->Transform()->SetRelativeScale(Vec3(1682.f, 980.f, 1.f));

	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI.png", L"texture\\BankUI.png", 0));
}

void CBankerFrameScript::tick()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		m_count++;
		if (m_count == 1)
		{
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_1.png", L"texture\\BankUI_1.png", 0));
		}
		else if (m_count == 2)
		{
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_2.png", L"texture\\BankUI_2.png", 0));
		}
		else if (m_count == 3)
		{
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_3.png", L"texture\\BankUI_3.png", 0));
		}
		else if (m_count == 4)
		{
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_4.png", L"texture\\BankUI_4.png", 0));
		}
		else if (m_count == 5)
		{
			MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_5.png", L"texture\\BankUI_5.png", 0));
		}
	}

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
