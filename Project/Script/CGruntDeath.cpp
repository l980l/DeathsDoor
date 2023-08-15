#include "pch.h"
#include "CGruntDeath.h"
#include "CGruntScript.h"
#include "CPlayerScript.h"
#include "CSoundScript.h"

void CGruntDeath::Enter()
{
	GetOwner()->Animator3D()->Play(13, false);
	GetOwner()->GetScript<CGruntScript>()->SetStarePlayer(false);

	// Sound
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Lurker\\Grunt_DashAttackVoice2.ogg", 1, 0.1f);
}

void CGruntDeath::tick()
{
	GetOwner()->Rigidbody()->ClearForce();
	
	// �ִϸ��̼��� ���� ��� ��� Paperburn ȿ�� �ֱ�.
	if (GetOwner()->Animator3D()->IsFinish())
	{
		GetOwner()->GetScript<CGruntScript>()->SetPaperBurnEffect(true);
		m_bStartPaperBurn = true;
		GetOwner()->Animator3D()->SetStop(true);
	}

	if (m_bStartPaperBurn)
		m_fPaperBurnTime += DT;

	// ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
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
