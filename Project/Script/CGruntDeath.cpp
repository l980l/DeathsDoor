#include "pch.h"
#include "CGruntDeath.h"
#include "CGruntScript.h"

void CGruntDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, false);
}

void CGruntDeath::tick()
{
	// 애니메이션이 끝난 경우 사망 Paperburn 효과 주기.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CGruntScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CGruntDeath::Exit()
{
}

CGruntDeath::CGruntDeath() :
	m_bStartPaperBurn(false)
	, m_fPaperBurnTime(0.f)
{
}

CGruntDeath::~CGruntDeath()
{
}
