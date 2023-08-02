#include "pch.h"
#include "CBazookaDeath.h"
#include "CBazookaScript.h"

void CBazookaDeath::Enter()
{
	GetOwner()->GetScript<CBazookaScript>()->SetPaperBurnEffect(true);
	// ���� ����� ������� �帥 �ð��� ����.
	m_bStartPaperBurn = true;
}

void CBazookaDeath::tick()
{
	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CBazookaDeath::Exit()
{
}

CBazookaDeath::CBazookaDeath() :
	m_bStartPaperBurn(false)
	, m_fPaperBurnTime(0.f)
{
}

CBazookaDeath::~CBazookaDeath()
{
}
