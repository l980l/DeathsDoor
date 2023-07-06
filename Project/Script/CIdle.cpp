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
	// 이동키를 눌렀다면 Walk 상태로 전환
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
