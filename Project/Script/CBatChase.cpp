#include "pch.h"
#include "CBatChase.h"

CBatChase::CBatChase()
{
}

CBatChase::~CBatChase()
{
}

void CBatChase::tick()
{
}

void CBatChase::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CBatChase::Exit()
{
}

void CBatChase::BeginOverlap(CCollider2D* _Other)
{
}

void CBatChase::OnOverlap(CCollider2D* _Other)
{
}

void CBatChase::EndOverlap(CCollider2D* _Other)
{
}
