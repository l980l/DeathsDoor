#include "pch.h"
#include "CBazookaDeath.h"
#include "CBazookaScript.h"
#include "CPlayerScript.h"
#include "CSoundScript.h"

void CBazookaDeath::Enter()
{
	GetOwner()->GetScript<CBazookaScript>()->SetPaperBurnEffect(true);
	GetOwner()->GetScript<CBazookaScript>()->SetStarePlayer(false);
	// ���� ����� ������� �帥 �ð��� ����.
	m_bStartPaperBurn = true;
	GetOwner()->Animator3D()->SetStop(true);

	// Sound
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Lurker\\PlagueBoyDeath.ogg", 1, 0.1f);
}

void CBazookaDeath::tick()
{
	GetOwner()->Rigidbody()->ClearForce();
	
	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
	if (m_fPaperBurnTime > 3.f && !GetOwner()->IsDead())
	{
		GetOwner()->GetScript<CBazookaScript>()->GetPlayer()->GetScript<CPlayerScript>()->AddMoney((UINT)600);
		GetOwnerScript()->Destroy();
	}
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
