#include "pch.h"
#include "CBazookaDeath.h"
#include "CBazookaScript.h"

void CBazookaDeath::Enter()
{
	GetOwner()->GetScript<CBazookaScript>()->SetPaperBurnEffect(true);
	// 몬스터 사망시 현재까지 흐른 시간을 저장.
	m_bStartPaperBurn = true;
}

void CBazookaDeath::tick()
{
	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
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
