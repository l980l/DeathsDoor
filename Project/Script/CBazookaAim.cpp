#include "pch.h"
#include "CBazookaAim.h"
#include "CBazookaScript.h"

void CBazookaAim::Enter()
{
	GetOwner()->Animator3D()->Play(0, true);
	m_fAimTime = 0.f;
}

void CBazookaAim::tick()
{
	m_fAimTime += DT;

	// 3초 이상 조준 중이면 발사.
	if (m_fAimTime >= 3.f)
		ChangeState(L"LongDistance");
}

void CBazookaAim::Exit()
{
}

CBazookaAim::CBazookaAim() :
	m_fAimTime(0.f)
{
}

CBazookaAim::~CBazookaAim()
{
}
