#include "pch.h"
#include "CPlyFall.h"
#include "CPlayerScript.h"

CPlyFall::CPlyFall()
{
}

CPlyFall::~CPlyFall()
{
}

void CPlyFall::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::FALL, true);
}

void CPlyFall::tick()
{
	if (GetOwner()->Rigidbody()->IsGround())
		GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
}

void CPlyFall::Exit()
{
}

void CPlyFall::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::FALLAREA)
	{
		Stat CurStat = GetOwnerScript()->GetStat();
		CurStat.HP -= 1;
		GetOwnerScript()->SetStat(CurStat);
	}

}

void CPlyFall::OnOverlap(CCollider3D* _Other)
{
}

void CPlyFall::EndOverlap(CCollider3D* _Other)
{
}
