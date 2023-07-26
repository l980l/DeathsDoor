#include "pch.h"
#include "CPlyWpMagic_Hooking.h"

CPlyWpMagic_Hooking::CPlyWpMagic_Hooking()
{
}

CPlyWpMagic_Hooking::~CPlyWpMagic_Hooking()
{
}

void CPlyWpMagic_Hooking::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOKING, false);
}

void CPlyWpMagic_Hooking::tick()
{
}

void CPlyWpMagic_Hooking::Exit()
{
}
