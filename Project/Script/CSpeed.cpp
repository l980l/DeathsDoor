#include "pch.h"
#include "CSpeed.h"

CSpeed::CSpeed()
{

}

CSpeed::~CSpeed()
{
}

void CSpeed::tick()
{
	if (KEY_TAP(KEY::UP))
	{
		ChangeState(L"AttackSpeed");
	}
	if (KEY_TAP(KEY::DOWN))
	{
		ChangeState(L"Magic");
	}
}

void CSpeed::Enter()
{
	GetOwner()->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\BankUI_Speed.png", L"texture\\BankUI_Speed.png", 0));
}

void CSpeed::Exit()
{
}

void CSpeed::BeginOverlap(CCollider2D* _Other)
{
}

void CSpeed::OnOverlap(CCollider2D* _Other)
{
}

void CSpeed::EndOverlap(CCollider2D* _Other)
{
}
