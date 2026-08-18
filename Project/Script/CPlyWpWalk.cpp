#include "pch.h"
#include "CPlyWpWalk.h"

void CPlyWpWalk::tick()
{
}

void CPlyWpWalk::Enter()
{
    GetOwner()->Animator3D()->Play(static_cast<int>(PLAYERANIM_TYPE::WALK), true);
}

void CPlyWpWalk::Exit()
{
}

CPlyWpWalk::CPlyWpWalk()
{
}

CPlyWpWalk::~CPlyWpWalk()
{
}
