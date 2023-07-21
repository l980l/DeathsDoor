#include "pch.h"
#include "CBatIdle.h"

CBatIdle::CBatIdle()
{
}

CBatIdle::~CBatIdle()
{
}

void CBatIdle::tick()
{
}

void CBatIdle::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(0, true);
}

void CBatIdle::Exit()
{
}

void CBatIdle::BeginOverlap(CCollider2D* _Other)
{
}

void CBatIdle::OnOverlap(CCollider2D* _Other)
{
}

void CBatIdle::EndOverlap(CCollider2D* _Other)
{
}
