#include "pch.h"
#include "CPlyWpIdle.h"

CPlyWpIdle::CPlyWpIdle()
{
}

CPlyWpIdle::~CPlyWpIdle()
{
}

void CPlyWpIdle::Enter()
{
    GetOwner()->Animator3D()->Play(static_cast<int>(PLAYERANIM_TYPE::IDLE), true);
}

void CPlyWpIdle::tick()
{
}

void CPlyWpIdle::Exit()
{
}
