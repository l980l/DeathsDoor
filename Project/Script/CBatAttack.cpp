#include "pch.h"
#include "CBatAttack.h"

CBatAttack::CBatAttack()
{
}

CBatAttack::~CBatAttack()
{
}

void CBatAttack::tick()
{
}

void CBatAttack::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(2, true);
}

void CBatAttack::Exit()
{

}

void CBatAttack::BeginOverlap(CCollider2D* _Other)
{
}

void CBatAttack::OnOverlap(CCollider2D* _Other)
{
}

void CBatAttack::EndOverlap(CCollider2D* _Other)
{
}
