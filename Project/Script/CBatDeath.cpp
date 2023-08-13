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

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CBatDeath::Enter()
{
	GetOwner()->GetScript<CBatScript>()->SetPaperBurnEffect(true);
	// 몬스터 사망시 현재까지 흐른 시간을 저장.
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
