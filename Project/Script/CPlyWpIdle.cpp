#include "pch.h"
#include "CPlyWpIdle.h"

void CPlyWpIdle::tick()
{
}

void CPlyWpIdle::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::IDLE, true);
}

void CPlyWpIdle::Exit()
{
}

CPlyWpIdle::CPlyWpIdle()
{
}

CPlyWpIdle::~CPlyWpIdle()
{
}
