#include "pch.h"
#include "CGruntDeath.h"
#include "CGruntScript.h"
#include "CPlayerScript.h"

void CGruntDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, false);
	GetOwner()->GetScript<CGruntScript>()->SetStarePlayer(false);
	GetOwner()->Rigidbody()->ClearForce();
}

void CGruntDeath::tick()
{
	// 애니메이션이 끝난 경우 사망 Paperburn 효과 주기.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CGruntScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
	if (m_fPaperBurnTime > 3.f && !GetOwner()->IsDead())
	{
		GetOwner()->GetScript<CGruntScript>()->GetPlayer()->GetScript<CPlayerScript>()->AddMoney((UINT)500);
		GetOwnerScript()->Destroy();
	}
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
