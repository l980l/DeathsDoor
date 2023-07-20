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
	if (KEY_TAP(KEY::LBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Attack");
	}
	else if (KEY_TAP(KEY::RBTN))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Magic");
	}
	// �̵�Ű�� �����ٸ� Walk ���·� ��ȯ
	else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Walk");
	}	
	else if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Dodge");
	}
}

void CPlyIdle::Enter()
{
	// Idle ���� �� Idle Anim �ݺ����
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::IDLE, true);
}

void CPlyIdle::Exit()
{
}
