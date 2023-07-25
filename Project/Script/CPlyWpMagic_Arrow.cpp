#include "pch.h"
#include "CPlyWpMagic_Arrow.h"

CPlyWpMagic_Arrow::CPlyWpMagic_Arrow()
	: m_fChargeDelay(0.f)
{
}

CPlyWpMagic_Arrow::~CPlyWpMagic_Arrow()
{
}

void CPlyWpMagic_Arrow::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::ARROW, false);
}

void CPlyWpMagic_Arrow::tick()
{
	m_fChargeDelay += DT;
	// 1�� ���� �����ϰ� ������ ���� ����
	if (m_fChargeDelay >= 1.f)
	{
		//if(R)
		// ������ ��ȯ�Ͽ� SetVelocity �� ��
	}
}

void CPlyWpMagic_Arrow::Exit()
{
	m_fChargeDelay = 0.f;
}
