#include "pch.h"
#include "CPlyMagic_Fire.h"

CPlyMagic_Fire::CPlyMagic_Fire()
	: m_fMagicChargeTime(0.f)
{
}

CPlyMagic_Fire::~CPlyMagic_Fire()
{
}

void CPlyMagic_Fire::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::MAGIC_FIRE, false);
}

void CPlyMagic_Fire::tick()
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

void CPlyMagic_Fire::Exit()
{
	m_fMagicChargeTime = 0.f;
}
