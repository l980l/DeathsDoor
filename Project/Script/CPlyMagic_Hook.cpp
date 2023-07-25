#include "pch.h"
#include "CPlyMagic_Hook.h"

CPlyMagic_Hook::CPlyMagic_Hook()
	: m_fMagicChargeTime(0.f)
{
}

CPlyMagic_Hook::~CPlyMagic_Hook()
{
}

void CPlyMagic_Hook::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
}

void CPlyMagic_Hook::tick()
{
}

void CPlyMagic_Hook::Exit()
{
}
