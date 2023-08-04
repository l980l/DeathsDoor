#include "pch.h"
#include "CLurkerDeath.h"
#include "CLurkerScript.h"

void CLurkerDeath::Enter()
{
	GetOwner()->Animator3D()->Play(6, false);
}

void CLurkerDeath::tick()
{
	// 애니메이션이 끝난 경우 사망 Paperburn 효과 주기.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CLurkerScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CLurkerDeath::Exit()
{
}

CLurkerDeath::CLurkerDeath() :
	m_bStartPaperBurn(false)
	, m_fPaperBurnTime(0.f)
{
}

CLurkerDeath::~CLurkerDeath()
{
}
