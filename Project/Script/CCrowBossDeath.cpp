#include "pch.h"
#include "CCrowBossDeath.h"
#include "CCrowBossScript.h"
#include "CPlayerScript.h"
#include "CSoundScript.h"

void CCrowBossDeath::Enter()
{
	GetOwner()->Animator3D()->Play(7, false);
	GetOwner()->GetScript<CCrowBossScript>()->SetStarePlayer(false);
	GetOwner()->GetScript<CCrowBossScript>()->DestoryFeather();

	// Sound
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\CrowBoss\\OldCrow_Death.ogg", 1, 0.1f);
}

void CCrowBossDeath::tick()
{
	GetOwner()->Rigidbody()->ClearForce();
	
	// �ִϸ��̼��� ���� ��� ��� Paperburn ȿ�� �ֱ�.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CCrowBossScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
	if (m_fPaperBurnTime > 3.f && !GetOwner()->IsDead())
	{
		GetOwner()->GetScript<CCrowBossScript>()->GetPlayer()->GetScript<CPlayerScript>()->AddMoney((UINT)30000);
		GetOwnerScript()->Destroy();

		CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetScript<CPlayerScript>()->ChangeState(L"Dance");
	}
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
