#include "pch.h"
#include "CPlyWpAttack.h"

void CPlyWpAttack::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
}

void CPlyWpAttack::tick()
{
	// ���ݸ���� �����ٸ� ���� ���ѽð� �ȿ� �����ϸ� �������� �ƴ϶�� Idle�� ��ȯ
	if (GetOwner()->Animator3D()->IsFinish())
	{
		// ���� ����Ƚ�� ����
		++m_iAttackCount;
		// Idle������ �ð� ����
		m_fAfterAttack += DT;
		if (KEY_TAP(KEY::LBTN))
		{
			// LimitTime ���� LBTN�� �����ٸ� ���� ��������
			m_fAfterAttack = 0.f;
			// ��ü ����Ƚ���� �����ٸ� Idle��
			if( m_iAttackCount > 3)
			{
				if (1 == m_iAttackCount)
					GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_L, false);
				else
					GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
			}
			m_fAfterAttack = 0.f;
		}
	}
}

void CPlyWpAttack::Exit()
{
	m_fAfterAttack = 0.f;
	m_iAttackCount = 0;
}

CPlyWpAttack::CPlyWpAttack()
{
}

CPlyWpAttack::~CPlyWpAttack()
{
}
