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
	// 1초 동안 차지하고 있으면 공격 가능
	if (m_fChargeDelay >= 1.f)
	{
		//if(R)
		// 프리팹 소환하여 SetVelocity 할 것
	}
}

void CPlyWpMagic_Arrow::Exit()
{
	m_fChargeDelay = 0.f;
}
