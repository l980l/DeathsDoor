#include "pch.h"
#include "CMagic.h"

CMagic::CMagic()
{
}

CMagic::~CMagic()
{
}

void CMagic::tick()
{
	if (KEY_TAP(KEY::UP))
	{
		ChangeState(L"Speed");
	}
	if (KEY_TAP(KEY::DOWN))
	{
		ChangeState(L"Power");
	}
}

void CMagic::Enter()
{
	GetOwner()->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\BankUI_Magic.png"));
}

void CMagic::Exit()
{
}

void CMagic::BeginOverlap(CCollider2D* _Other)
{
}

void CMagic::OnOverlap(CCollider2D* _Other)
{
}

void CMagic::EndOverlap(CCollider2D* _Other)
{
}
