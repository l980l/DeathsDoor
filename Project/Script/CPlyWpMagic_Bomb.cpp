#include "pch.h"
#include "CPlyWpMagic_Bomb.h"

CPlyWpMagic_Bomb::CPlyWpMagic_Bomb()
{
}

CPlyWpMagic_Bomb::~CPlyWpMagic_Bomb()
{
}

void CPlyWpMagic_Bomb::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB, false);
}

void CPlyWpMagic_Bomb::tick()
{
}

void CPlyWpMagic_Bomb::Exit()
{
}
