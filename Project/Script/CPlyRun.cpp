#include "pch.h"
#include "CPlyRun.h"
#include "CPlayerScript.h"
#include "CSoundScript.h"

CPlyRun::CPlyRun()
	: m_fSpeed(0.f)
	, m_fTimeToIdle(0.f)
	, m_fRotDelay(0.f)
	, m_fRot(0.f)
	, m_bIce(false)
	, m_fStepSoundDelay(0.f)
	, m_bStepSoundOrder(false)
{
}

CPlyRun::~CPlyRun()
{
}

void CPlyRun::Enter()
{
	m_fSpeed = GetOwnerScript()->GetStat().Speed;
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::RUN, true);
}

void CPlyRun::tick()
{
	if (KEY_TAP(KEY::V))
		m_bIce = m_bIce ? false : true;
	Move();

	// ������ �ִٸ�(���� �����Ӱ� ��ġ ���̰� ���ٸ�) Idle ��ȯ�ð� +
	if (!(KEY_PRESSED(KEY::W)) && !(KEY_PRESSED(KEY::A)) && !(KEY_PRESSED(KEY::S)) && !(KEY_PRESSED(KEY::D)))
	{
		m_fTimeToIdle += DT;
	}
	else
	{
		GetOwner()->Transform()->CalcDir();
		m_fTimeToIdle = 0.f;
	}

	if (KEY_TAP(KEY::LBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Attack");
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeMagicState();
	}
	// Idle ��ȯ�ð��� 0.1�� �Ѿ��ٸ� Idle��
	else if (m_fTimeToIdle >= 0.02f)
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Walk");
	}
	else if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}
}

void CPlyRun::Exit()
{
	m_fTimeToIdle = 0.f;
	m_fStepSoundDelay = 0.f;
	if(!m_bIce)
		GetOwner()->Rigidbody()->ClearForce();
}

void CPlyRun::Move()
{
	Vec3 Velocity = Vec3(0.f, 0.f, 0.f);

	if (KEY_PRESSED(KEY::W))
	{
		Velocity.z += 1.f;
	}						  
							  
	if (KEY_PRESSED(KEY::S))  
	{						  
		Velocity.z -= 1.f;
	}						  
							  
	if (KEY_PRESSED(KEY::A))  
	{						  
		Velocity.x -= 1.f;
	}						  
							  
	if (KEY_PRESSED(KEY::D))  
	{						  
		Velocity.x += 1.f;
	}
	Velocity.Normalize();

	Velocity *= m_fSpeed;

	if (m_bIce)
		GetOwner()->Rigidbody()->AddForce(Velocity * DT * 15.f);
	else
		GetOwner()->Rigidbody()->SetVelocity(Velocity);

	m_fStepSoundDelay += DT;

	if (m_fStepSoundDelay > 0.15f)
	{
		wstring wstrSoundFilePath;
		if (m_bStepSoundOrder)
			wstrSoundFilePath = L"Sound\\Player\\GrassFootStepL.mp3";
		else
			wstrSoundFilePath = L"Sound\\Player\\GrassFootStepR.mp3";
		CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = soundscript->AddSound(wstrSoundFilePath, 1,1.f);
		m_fStepSoundDelay = 0.f;
	}
}

void CPlyRun::BeginOverlap(CCollider3D* _Other)
{
}

void CPlyRun::OnOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER && KEY_PRESSED(KEY::E))
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}
