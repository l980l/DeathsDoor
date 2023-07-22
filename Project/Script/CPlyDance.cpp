#include "pch.h"
#include "CPlyDance.h"
#include "CPlayerScript.h"

CPlyDance::CPlyDance()
{
}

CPlyDance::~CPlyDance()
{
}

void CPlyDance::Enter()
{
	// 승리했을 때 춤출 것? 같아서 무적 변환
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::DANCE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDance::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
}

void CPlyDance::Exit()
{
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}
