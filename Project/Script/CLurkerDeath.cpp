#include "pch.h"
#include "CLurkerDeath.h"
#include "CLurkerScript.h"
#include "CPlayerScript.h"
#include "CSoundScript.h"

void CLurkerDeath::Enter()
{
	GetOwner()->Animator3D()->Play(6, false);
	GetOwner()->GetScript<CLurkerScript>()->SetStarePlayer(false);

	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Lurker\\LurkerDeath1.ogg", 1, 0.1f);
}

void CLurkerDeath::tick()
{
	GetOwner()->Rigidbody()->ClearForce();
	
	m_fTime += DT;

	float fPlayRatio = m_fTime / GetOwner()->Animator3D()->GetCurClipTimeLength();

	// �ִϸ��̼��� ���� ��� ��� Paperburn ȿ�� �ֱ�.
	if (fPlayRatio >= 0.8f && !m_bStartPaperBurn)
	{
		GetOwner()->GetScript<CLurkerScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
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
