#include "pch.h"
#include "CGruntJumpAttack.h"
#include "CGruntScript.h"

void CGruntJumpAttack::Enter()
{
	GetOwner()->Animator3D()->Play(12, false);

	// ���� ������ ó������ �����ؾ� ��. 
	m_Dir = GetOwner()->GetScript<CGruntScript>()->GetMonsterToPlayerDir();
	GetOwner()->Rigidbody()->SetVelocityLimit(300.f);

	float fDir = GetDir(GetOwner()->Transform()->GetWorldPos(), GetOwner()->GetScript<CGruntScript>()->GetPlayerPos());
	Vec3 CurDir = GetOwner()->Transform()->GetRelativeRot();
	GetOwner()->Transform()->SetRelativeRot(CurDir.x, fDir, 0.f);
}

void CGruntJumpAttack::tick()
{
	float AnimLength = (float)GetOwner()->Animator3D()->GetCurClipTimeLength();
	m_fTime += DT;
	float CurRatio = m_fTime / AnimLength;

	if (CurRatio <= 0.5f)
	{
		Vec3 Velocity = m_Dir;
		float fSpeed = GetOwnerScript()->GetStat().Speed;
		Velocity *= fSpeed * 30.f * DT;

		GetOwner()->Rigidbody()->AddVelocity(Velocity);
	}

	if(CurRatio > 0.65f)
		GetOwner()->Rigidbody()->ClearForce();

	// �ִϸ��̼��� ������ Run2�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Run2");
}

void CGruntJumpAttack::Exit()
{
	GetOwner()->Rigidbody()->ClearForce();
	m_fTime = 0.f;
}

CGruntJumpAttack::CGruntJumpAttack() :
	m_fTime(0.f)
{
}

CGruntJumpAttack::~CGruntJumpAttack()
{
}
