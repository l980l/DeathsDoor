#include "pch.h"
#include "CPlyCharge.h"


CPlyCharge::CPlyCharge()
	: m_fMaxChargeTime(0.f)
{
}

CPlyCharge::~CPlyCharge()
{
}

void CPlyCharge::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::CHARGE_ATTACK_L)
}

void CPlyCharge::tick()
{
}

void CPlyCharge::Exit()
{
}
