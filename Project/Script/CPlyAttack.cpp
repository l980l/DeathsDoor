#include "pch.h"
#include "CPlyAttack.h"
#include "CPlayerScript.h"

CPlyAttack::CPlyAttack()
	: m_iAttackCount(0)
	, m_fAfterAttack(0.f)
	, m_fLimitTimeNextAttack(0.3f)
{
}

CPlyAttack::~CPlyAttack()
{
}

void CPlyAttack::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
}

void CPlyAttack::tick()
{
	// 공격모션이 끝났다면 이후 제한시간 안에 공격하면 다음공격 아니라면 Idle로 전환
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// 현재 공격횟수 증가
		++m_iAttackCount;
		// Idle까지의 시간 증가
		m_fAfterAttack += DT;
		if(KEY_TAP(KEY::LBTN))
		{
			// LimitTime 전에 LBTN을 눌렀다면 다음 공격으로
			m_fAfterAttack = 0.f;
			// 전체 공격횟수가 끝났다면 Idle로
			if (m_iAttackCount <= 3)
				GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
			else
			{
				if (1 == m_iAttackCount)
					GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_L, false);
				else
					GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
			}
			m_fAfterAttack = 0.f;
		}
		else		
		{
			if (m_fAfterAttack >= m_fLimitTimeNextAttack)
				GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
}

void CPlyAttack::Exit()
{
	m_fAfterAttack = 0.f;
	m_iAttackCount = 0;
}
