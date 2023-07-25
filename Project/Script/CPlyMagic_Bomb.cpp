#include "pch.h"
#include "CPlyMagic_Bomb.h"

CPlyMagic_Bomb::CPlyMagic_Bomb()
	: m_fMagicChargeTime(0.f)
{
}

CPlyMagic_Bomb::~CPlyMagic_Bomb()
{
}

void CPlyMagic_Bomb::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_BOMB, false);
}

void CPlyMagic_Bomb::tick()
{
	m_fMagicChargeTime -= DT;
	if (m_fMagicChargeTime <= 0.f)
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			//Ptr<CPrefab> pArrowPref = CResMgr::GetInst()->FindRes<CPrefab>(L"Arrow");
			//CGameObject* pArrow = pArrowPref->Instantiate();
			//pArrow->Rigidbody()->AddVelocity(Vec3(0.f, 0.f, 0.f));
		}
	}
}

void CPlyMagic_Bomb::Exit()
{
	m_fMagicChargeTime = 0.f;
}
