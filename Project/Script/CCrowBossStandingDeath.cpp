#include "pch.h"
#include "CCrowBossStandingDeath.h"
#include "CCrowBossScript.h"

void CCrowBossStandingDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, false);
}

void CCrowBossStandingDeath::tick()
{
	// �ִϸ��̼��� ���� ��� ��� Paperburn ȿ�� �ֱ�.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CCrowBossScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
	if (m_fPaperBurnTime > 3.f)
		GetOwnerScript()->Destroy();
}

void CCrowBossStandingDeath::Exit()
{
}

CCrowBossStandingDeath::CCrowBossStandingDeath() :
	m_bStartPaperBurn(false)
	, m_fPaperBurnTime(0.f)
{
}

CCrowBossStandingDeath::~CCrowBossStandingDeath()
{
}
