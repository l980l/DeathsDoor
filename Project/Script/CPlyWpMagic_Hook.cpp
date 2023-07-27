#include "pch.h"
#include "CPlyWpMagic_Hook.h"

CPlyWpMagic_Hook::CPlyWpMagic_Hook()
{
}

CPlyWpMagic_Hook::~CPlyWpMagic_Hook()
{
}

void CPlyWpMagic_Hook::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
}

void CPlyWpMagic_Hook::tick()
{
}

void CPlyWpMagic_Hook::Exit()
{
}
