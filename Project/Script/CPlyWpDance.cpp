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
	GetOwner()->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::DANCE, false);
}

void CPlyWpDance::tick()
{
}

void CPlyWpDance::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(1.f, 1.f, 1.f);
}
