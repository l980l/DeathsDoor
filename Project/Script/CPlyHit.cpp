#include "pch.h"
#include "CPlyHit.h"
#include "CPlayerScript.h"

CPlyHit::CPlyHit()
{
}

CPlyHit::~CPlyHit()
{
}

void CPlyHit::tick()
{
	//if (GetOwner()->Animator3D()->IsFinish())
	//	GetOwnerScript()->ChangeState(L"Idle");
}

void CPlyHit::Enter()
{
	// Hit Anim ��� ������ �ٷ� Idle�� ���ư��� �ϹǷ� �ݺ���� false;
	//GetOwner()->Animator3D()->Play(, false);
	// �̹� Hit�̹Ƿ� ���� Ȱ��ȭ
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyHit::Exit()
{
	// ���� ��Ȱ��ȭ
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(false);
}

void CPlyHit::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyHit::OnOverlap(CCollider2D* _Other)
{
}

void CPlyHit::EndOverlap(CCollider2D* _Other)
{
}
