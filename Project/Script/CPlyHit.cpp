#include "pch.h"
#include "CPlyHit.h"
#include "CPlayerScript.h"

CPlyHit::CPlyHit()
{
}

CPlyHit::~CPlyHit()
{
}

void CPlyHit::Enter()
{
	// Hit Anim ��� ������ �ٷ� Idle�� ���ư��� �ϹǷ� �ݺ���� false;
	GetOwner()->Animator3D()->Play(22, false);
	// �̹� Hit�̹Ƿ� ���� Ȱ��ȭ
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyHit::tick()
{
	if(GetOwner()->Animator3D()->IsFinish())
	{
		if (GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::HIT)
		{
			GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HIT_RECOVER, false);
		}
		else
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
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
