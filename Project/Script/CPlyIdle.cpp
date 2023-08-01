#include "pch.h"
#include "CPlyIdle.h"
#include "CPlayerScript.h"

CPlyIdle::CPlyIdle()
{
}

CPlyIdle::~CPlyIdle()
{
}

void CPlyIdle::tick()
{
	return;
	if (KEY_TAP(KEY::LBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Attack");
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeMagicState();
	}
	// 이동키를 눌렀다면 Walk 상태로 전환
	else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
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

void CPlyIdle::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::LADDER)
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Ladder");
}
