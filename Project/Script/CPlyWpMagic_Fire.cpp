#include "pch.h"
#include "CPlyWpMagic_Fire.h"

CPlyWpMagic_Fire::CPlyWpMagic_Fire()
{
}

CPlyWpMagic_Fire::~CPlyWpMagic_Fire()
{
}

void CPlyWpMagic_Fire::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_FIRE, false);
}

void CPlyWpMagic_Fire::tick()
{
}

void CPlyWpMagic_Fire::Exit()
{
}

