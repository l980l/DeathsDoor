#include "pch.h"
#include "CPlyIdle.h"

CPlyIdle::CPlyIdle()
{
}

CPlyIdle::~CPlyIdle()
{
}

void CPlyIdle::tick()
{
	if (KEY_TAP(KEY::LBTN))
	{
		ChangeState(L"Charge");
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		ChangeState(L"Magic");
	}
	// 이동키를 눌렀다면 Walk 상태로 전환
	else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
		ChangeState(L"Walk");
	}	
}

void CPlyIdle::Enter()
{
	// Idle 진입 시 Idle Anim 반복재생
	GetOwner()->Animator3D()->Play(0, true);
}

void CPlyIdle::Exit()
{
}

void CPlyIdle::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyIdle::OnOverlap(CCollider2D* _Other)
{
}

void CPlyIdle::EndOverlap(CCollider2D* _Other)
{
}
