#include "pch.h"
#include "CBatDeath.h"

CBatDeath::CBatDeath()
{
}

CBatDeath::~CBatDeath()
{
}

void CBatDeath::tick()
{
}

void CBatDeath::Enter()
{
	//��� �� ������ �� ȿ��
	GetOwner()->SetLifeSpan(0.5f);
}

void CBatDeath::Exit()
{
}

void CBatDeath::BeginOverlap(CCollider2D* _Other)
{
}

void CBatDeath::OnOverlap(CCollider2D* _Other)
{
}

void CBatDeath::EndOverlap(CCollider2D* _Other)
{
}
