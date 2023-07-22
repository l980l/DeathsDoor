#include "pch.h"
#include "CPlyWpLadder.h"

void CPlyWpLadder::tick()
{
}

void CPlyWpLadder::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::LADDER_UP, true);
}

void CPlyWpLadder::Exit()
{
}

CPlyWpLadder::CPlyWpLadder()
{
}

CPlyWpLadder::~CPlyWpLadder()
{
}
