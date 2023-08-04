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
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HIT, false);
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
	GetOwner()->Rigidbody()->ClearForce();
}

void CPlyHit::BeginOverlap(CCollider3D* _Other)
{
}

void CPlyHit::OnOverlap(CCollider3D* _Other)
{
}

void CPlyHit::EndOverlap(CCollider3D* _Other)
{
}
