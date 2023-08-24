#include "pch.h"
#include "CBatRecognize.h"

CBatRecognize::CBatRecognize()
{
}

CBatRecognize::~CBatRecognize()
{
}

void CBatRecognize::tick()
{
	if(GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"BatTrace");
}

void CBatRecognize::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);
}

void CBatRecognize::Exit()
{
}
