#include "pch.h"
#include "CPlyAttack.h"
#include "CPlayerScript.h"
#include "CPlyWpAttack.h"

#include <Engine/CDevice.h>

CPlyAttack::CPlyAttack()
	: m_iAttackCount(0)
	, m_fAfterAttack(0.f)
	, m_fAttackDelay(0.f)
	, m_fLimitTimeNextAttack(0.15f)
{
}

CPlyAttack::~CPlyAttack()
{
}

void CPlyAttack::Enter()
{
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
	CalcDir();
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
}

void CPlyAttack::tick()
{
	// 공격모션이 끝났다면 이후 제한시간 안에 공격하면 다음공격 아니라면 Idle로 전환
	m_fAttackDelay += DT;
	if (GetOwner()->Animator3D()->IsFinish() || m_fAttackDelay >= 0.35f)
	{
		if (0.f == m_fAfterAttack)
			++m_iAttackCount;
		// 공격 모션이 끝나고 첫 번째 tick에만 현재 공격횟수가 증가하게 함
		// Idle까지의 시간 증가
		m_fAfterAttack += DT;

		// 공격 3회가 끝났거나, 공격모션이 끝나도 추가 공격을 입력하지 않은 경우 Idle로 전환
		if (m_iAttackCount >= 3 || m_fAfterAttack >= m_fLimitTimeNextAttack)
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
		else if(KEY_PRESSED(KEY::LBTN))
		{
			CalcDir();

			// 무기에도 공격횟수를 알려줌.
			CPlyWpAttack* pWpAttackState = (CPlyWpAttack*)GetOwner()->GetChild()[0]->GetScript<CStateScript>()->FindState(L"Attack");
			pWpAttackState->SetAttackCount(m_iAttackCount);

			// 좌우 번갈아 공격함
			if (GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::SLASH_R)
				GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_L, false);
			else
				GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);

			m_fAfterAttack = 0.f;
			m_fAttackDelay = 0.f;
		}
	}
}

void CPlyAttack::Exit()
{
	m_iAttackCount = 0;
	m_fAttackDelay = 0.f;
	m_fAfterAttack = 0.f;
}

void CPlyAttack::CalcDir()
{	
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	
	Vec3 AttackDir = Vec3(0.f, 0.f, 0.f);
	AttackDir = Vec3(0.f, 0.f, 0.f) - vMousePos;
	AttackDir.Normalize();
	AttackDir *= 500.f;
	AttackDir.y = 0.f;
	GetOwner()->Rigidbody()->AddVelocity(-AttackDir);
}
