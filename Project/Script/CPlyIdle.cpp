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
	// �̵�Ű�� �����ٸ� Walk ���·� ��ȯ
	else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
		ChangeState(L"Walk");
	}	
}

void CPlyIdle::Enter()
{
	// Idle ���� �� Idle Anim �ݺ����
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
