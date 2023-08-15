#include "pch.h"
#include "CLurkerRightMove.h"
#include "CLurkerScript.h"
#include "CSoundScript.h"

void CLurkerRightMove::Enter()
{
	GetOwner()->Animator3D()->Play(8, true);

	// Sound
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Lurker\\LurkerStep4.ogg", 1, 0.1f);
}

void CLurkerRightMove::tick()
{
	m_fTime += DT;

	// �÷��̾ �������� �������� �̵�.
	Vec3 Velocity = GetOwner()->GetScript<CLurkerScript>()->GetMonsterToPlayerDir();
	float fSpeed = GetOwnerScript()->GetStat().Speed;
	Velocity *= fSpeed;
	swap(Velocity.x, Velocity.z);
	Velocity.x *= -1.f;

	GetOwner()->Rigidbody()->SetVelocity(Velocity);

	// ���� �ð� ���� �̵��ϰ� ��.
	if (m_fTime > 1.f)
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
		ChangeState(L"Notify");
	}
}

void CLurkerRightMove::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
	m_fTime = 0.f;
}

CLurkerRightMove::CLurkerRightMove() :
	m_fTime(0.f)
{
}

CLurkerRightMove::~CLurkerRightMove()
{
}
