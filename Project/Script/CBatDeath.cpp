#include "pch.h"
#include "CBatDeath.h"
#include "CBatScript.h"

CBatDeath::CBatDeath()	:
m_bStartPaperBurn(false),
m_fPaperBurnTime(0.f)
{
}

CBatDeath::~CBatDeath()
{
}

void CBatDeath::tick()
{
	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CBatDeath::Enter()
{
	GetOwner()->GetScript<CBatScript>()->SetPaperBurnEffect(true);
	// ���� ����� ������� �帥 �ð��� ����.
	m_bStartPaperBurn = true;
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
