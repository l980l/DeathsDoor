#include "pch.h"
#include "CLurkerDeath.h"
#include "CLurkerScript.h"
#include "CPlayerScript.h"

void CLurkerDeath::Enter()
{
	GetOwner()->Animator3D()->Play(6, false);
	GetOwner()->GetScript<CLurkerScript>()->SetStarePlayer(false);
	GetOwner()->Rigidbody()->ClearForce();
}

void CLurkerDeath::tick()
{
	m_fTime += DT;

	float fPlayRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();

	// 애니메이션이 끝난 경우 사망 Paperburn 효과 주기.
	if (fPlayRatio >= 0.8f && !m_bStartPaperBurn)
	{
		GetOwner()->GetScript<CLurkerScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// 지금까지 흐른 시간이 3초 이상이면 Destory.
	if (m_fPaperBurnTime > 3.f && !GetOwner()->IsDead())
	{
		GetOwner()->GetScript<CLurkerScript>()->GetPlayer()->GetScript<CPlayerScript>()->AddMoney((UINT)200);
		GetOwnerScript()->Destroy();
	}
}

void CLurkerDeath::Exit()
{
}

CLurkerDeath::CLurkerDeath() :
	m_bStartPaperBurn(false)
	, m_fPaperBurnTime(0.f)
	, m_fTime(0.f)
{
}

CLurkerDeath::~CLurkerDeath()
{
}
