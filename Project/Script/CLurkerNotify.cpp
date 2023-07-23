#include "pch.h"
#include "CLurkerNotify.h"
#include "CLurkerScript.h"

void CLurkerNotify::Enter()
{
	// AnimClip 이름은 ReadyAction임
	GetOwner()->Animator3D()->Play(1, false);
}

void CLurkerNotify::tick()
{
	// 이미 Notify 행동을 한적이 있다면 다른 상태로.
	if (m_bNotify)
	{

	}

	// 현재 진행중인 ReadyAction 애니메이션이 끝났다면 m_bNotify를 true로 변경.
	else
	{
		if (GetOwner()->Animator3D()->IsFinish())
			m_bNotify = true;

		// 애니메이션 재생 시간 동안 플레이어를 바라보도록 회전해야 함.
	}
}

void CLurkerNotify::Exit()
{
}

CLurkerNotify::CLurkerNotify() :
	m_bNotify(false)
{
}

CLurkerNotify::~CLurkerNotify()
{
}
