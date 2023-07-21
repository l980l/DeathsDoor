#include "pch.h"
#include "CBatChase.h"

void CBatChase::tick()
{
}

void CBatChase::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
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

CBatChase::CBatChase()
{
}

CBatChase::~CBatChase()
{
}
