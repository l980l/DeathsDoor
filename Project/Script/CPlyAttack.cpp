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
	// ���ݸ���� �����ٸ� ���� ���ѽð� �ȿ� �����ϸ� �������� �ƴ϶�� Idle�� ��ȯ
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// ���� ����Ƚ�� ����
		++m_iAttackCount;
		// Idle������ �ð� ����
		m_fAfterAttack += DT;
		if(KEY_TAP(KEY::LBTN))
		{
			// LimitTime ���� LBTN�� �����ٸ� ���� ��������
			m_fAfterAttack = 0.f;
			// ��ü ����Ƚ���� �����ٸ� Idle��
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
