#include "pch.h"
#include "CPlyWpFall.h"

CPlyWpFall::CPlyWpFall()
{
}

CPlyWpFall::~CPlyWpFall()
{
}

void CPlyWpFall::Enter()
{
    GetOwner()->Animator3D()->Play(static_cast<int>(PLAYERANIM_TYPE::FALL), false);
}

void CPlyWpFall::tick()
{
}

void CPlyWpFall::Exit()
{
}
