#include "pch.h"
#include "CGrimKnightDeath.h"
#include "CGrimKnightScript.h"

CGrimKnightDeath::CGrimKnightDeath()		:
	m_bStartPaperBurn(false),
	m_fPaperBurnTime(0.f)
{
}

CGrimKnightDeath::~CGrimKnightDeath()
{
}

void CGrimKnightDeath::tick()
{
	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CGrimKnightDeath::Enter()
{
	GetOwner()->GetScript<CGrimKnightScript>()->SetPaperBurnEffect(true);
	// ���� ����� ������� �帥 �ð��� ����.
	m_bStartPaperBurn = true;
}

void CGrimKnightDeath::Exit()
{
}

void CGrimKnightDeath::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightDeath::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightDeath::EndOverlap(CCollider2D* _Other)
{
}
