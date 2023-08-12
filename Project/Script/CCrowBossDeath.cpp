#include "pch.h"
#include "CCrowBossDeath.h"
#include "CCrowBossScript.h"

void CCrowBossDeath::Enter()
{
	GetOwner()->Animator3D()->Play(7, false);
	GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(false);
}

void CCrowBossDeath::tick()
{
	// 애니메이션이 끝난 경우 사망 Paperburn 효과 주기.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CCrowBossScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CCrowBossDeath::Exit()
{
}

CCrowBossDeath::CCrowBossDeath() :
	m_bStartPaperBurn(false)
	, m_fPaperBurnTime(0.f)
{
}

CCrowBossDeath::~CCrowBossDeath()
{
}
