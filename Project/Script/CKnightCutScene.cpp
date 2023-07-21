#include "pch.h"
#include "CKnightCutScene.h"

void CKnightCutScene::tick()
{
}

void CKnightCutScene::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(4, false);
}

void CKnightCutScene::Exit()
{
}

void CKnightCutScene::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightCutScene::OnOverlap(CCollider2D* _Other)
{
}

void CKnightCutScene::EndOverlap(CCollider2D* _Other)
{
}

CKnightCutScene::CKnightCutScene()
{
}

CKnightCutScene::~CKnightCutScene()
{
}
