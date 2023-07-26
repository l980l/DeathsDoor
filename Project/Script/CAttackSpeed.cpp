#include "pch.h"
#include "CAttackSpeed.h"

CAttackSpeed::CAttackSpeed()
{
}

CAttackSpeed::~CAttackSpeed()
{
}

void CAttackSpeed::tick()
{
	if (KEY_TAP(KEY::UP))
	{
		ChangeState(L"Power");
	}
	if (KEY_TAP(KEY::DOWN))
	{
		ChangeState(L"Speed");
	}
}

void CAttackSpeed::Enter()
{
	GetOwner()->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\BankUI_AttackSpeed.png"));
}

void CAttackSpeed::Exit()
{
}

void CAttackSpeed::BeginOverlap(CCollider2D* _Other)
{
}

void CAttackSpeed::OnOverlap(CCollider2D* _Other)
{
}

void CAttackSpeed::EndOverlap(CCollider2D* _Other)
{
}
