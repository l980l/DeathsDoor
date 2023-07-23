#include "pch.h"
#include "CPlyWpDance.h"

CPlyWpDance::CPlyWpDance()
{
}

CPlyWpDance::~CPlyWpDance()
{
}

void CPlyWpDance::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::DANCE, false);
}

void CPlyWpDance::tick()
{
}

void CPlyWpDance::Exit()
{
}
