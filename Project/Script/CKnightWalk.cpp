#include "pch.h"
#include "CKnightWalk.h"
#include "CSoundScript.h"
#include <Engine/CDetourMgr.h>

CKnightWalk::CKnightWalk()
{
}

CKnightWalk::~CKnightWalk()
{
}

void CKnightWalk::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(1, true);
}

void CKnightWalk::tick()
{
	Vec3 m_Dir = CLevelMgr::GetInst()->FindObjectByName(L"Player")->Transform()->GetRelativePos() - GetOwner()->Transform()->GetRelativePos();
	m_Dir.Normalize();
	Vec3 Velocity = m_Dir;
	float fSpeed = GetOwnerScript()->GetStat().Speed / 2.f;
	Velocity *= fSpeed;

	GetOwner()->Rigidbody()->SetVelocity(Velocity);


	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Knight\\PoshKnightPreStep1.ogg", 1, 0.2);
}

void CKnightWalk::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
}
