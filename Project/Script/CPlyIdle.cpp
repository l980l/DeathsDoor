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
	// �̵�Ű�� �����ٸ� Walk ���·� ��ȯ
	if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
		ChangeState(L"Walk");
}

void CPlyIdle::Enter()
{
	// Idle ���� �� Idle Anim �ݺ����
	//GetOwner()->Animator3D()->Play( , true);
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
