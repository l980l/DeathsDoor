#include "pch.h"
#include "CPlyWpMagic_Arrow.h"

CPlyWpMagic_Arrow::CPlyWpMagic_Arrow()
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
}

void CPlyWpMagic_Arrow::Exit()
{
}
