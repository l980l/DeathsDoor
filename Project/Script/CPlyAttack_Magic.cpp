#include "pch.h"
#include "CPlyAttack_Magic.h"
#include "CPlayerScript.h"

CPlyAttack_Magic::CPlyAttack_Magic()
{
}

CPlyAttack_Magic::~CPlyAttack_Magic()
{
}

void CPlyAttack_Magic::Enter()
{
	UINT CurMagie = GetOwner()->GetScript<CPlayerScript>()->GetUseMagic();

	switch ((PLAYER_MAGIC)CurMagie)
	{
	case PLAYER_MAGIC::ARROW:
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::ARROW, false);
		m_fMagicChargeTime = 1.f;
		break;
	case PLAYER_MAGIC::FIRE:
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_FIRE, false);
		m_fMagicChargeTime = 1.3f;
		break;
	case PLAYER_MAGIC::BOMB:
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB, false);
		m_fMagicChargeTime = 2.f;
		break;
	case PLAYER_MAGIC::HOOK:
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
		m_fMagicChargeTime = 0.1f;
		break;
	}
}

void CPlyAttack_Magic::tick()
{
}

void CPlyAttack_Magic::Exit()
{
}

void CPlyAttack_Magic::BeginOverlap(CCollider2D* _Other)
{
}

void CPlyAttack_Magic::OnOverlap(CCollider2D* _Other)
{
}

void CPlyAttack_Magic::EndOverlap(CCollider2D* _Other)
{
}
