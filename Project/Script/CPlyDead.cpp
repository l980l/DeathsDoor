#include "pch.h"
#include "CPlyDead.h"
#include "CPlayerScript.h"

CPlyDead::CPlyDead()
{
}

CPlyDead::~CPlyDead()
{
}

void CPlyDead::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HIT_IDLE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDead::tick()
{
	// ��� �۾��� ȭ���� �����鼭 Hall Level���� �ٽ� ����
}

void CPlyDead::Exit()
{
}
