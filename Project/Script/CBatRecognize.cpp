#include "pch.h"
#include "CBatRecognize.h"

CBatRecognize::CBatRecognize()
{
}

CBatRecognize::~CBatRecognize()
{
}

void CBatRecognize::tick()
{
}

void CBatRecognize::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(1, true);
}

void CBatRecognize::Exit()
{
}

void CBatRecognize::BeginOverlap(CCollider2D* _Other)
{
}

void CBatRecognize::OnOverlap(CCollider2D* _Other)
{
}

void CBatRecognize::EndOverlap(CCollider2D* _Other)
{
}
