#include "pch.h"
#include "CIdle.h"

CIdle::CIdle()
{
}

CIdle::~CIdle()
{
}

void CIdle::tick()
{
	// �̵�Ű�� �����ٸ� Walk ���·� ��ȯ
	if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
		ChangeState(L"Walk");
}

void CIdle::Enter()
{
}

void CIdle::Exit()
{
}

void CIdle::BeginOverlap(CCollider2D* _Other)
{
}

void CIdle::OnOverlap(CCollider2D* _Other)
{
}

void CIdle::EndOverlap(CCollider2D* _Other)
{
}
