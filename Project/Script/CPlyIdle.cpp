#include "pch.h"
#include "CPlyIdle.h"
#include "CPlayerScript.h"

CPlyIdle::CPlyIdle()
	:m_bWalk(false)
{
}

CPlyIdle::~CPlyIdle()
{
}

void CPlyIdle::tick()
{
	if (KEY_TAP(KEY::LBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Attack");
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Magic");
	}
	// 이동키를 눌렀다면 Walk 상태로 전환
	else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
		if(m_bWalk)
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Walk");
		else
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Run");
	}	
	else if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}
}

void CPlyIdle::Enter()
{
	// Idle 진입 시 Idle Anim 반복재생
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::IDLE, true);
}

void CPlyIdle::Exit()
{
}
