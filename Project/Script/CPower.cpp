#include "pch.h"
#include "CPower.h"

CPower::CPower()
{
}

CPower::~CPower()
{
}

void CPower::tick()
{
	if (KEY_TAP(KEY::UP))
	{
		ChangeState(L"Magic");
	}
	if (KEY_TAP(KEY::DOWN))
	{
		ChangeState(L"AttackSpeed");
	}
}

void CPower::Enter()
{
	GetOwner()->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_Power.png", L"texture\\BankUI_Power.png", 0));
}

void CPower::Exit()
{
}

void CPower::BeginOverlap(CCollider2D* _Other)
{
}

void CPower::OnOverlap(CCollider2D* _Other)
{
}

void CPower::EndOverlap(CCollider2D* _Other)
{
}
