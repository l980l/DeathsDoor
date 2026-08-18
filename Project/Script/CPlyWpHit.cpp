#include "pch.h"
#include "CPlyWpHit.h"

CPlyWpHit::CPlyWpHit()
{
}

CPlyWpHit::~CPlyWpHit()
{
}

void CPlyWpHit::Enter()
{
    GetOwner()->Animator3D()->Play(static_cast<int>(PLAYERANIM_TYPE::HIT), false);
}

void CPlyWpHit::tick()
{
    if (GetOwner()->Animator3D()->IsFinish())
        if (GetOwner()->Animator3D()->GetCurClip() == static_cast<int>(PLAYERANIM_TYPE::HIT))
            GetOwner()->Animator3D()->Play(static_cast<int>(PLAYERANIM_TYPE::HIT_RECOVER), false);
}

void CPlyWpHit::Exit()
{
}
