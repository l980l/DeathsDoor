#include "pch.h"
#include "CPlyMagic_Arrow.h"
#include <Engine/CDevice.h>

CPlyMagic_Arrow::CPlyMagic_Arrow()
	: m_fMagicChargeTime(0.f)
	, m_pBow(nullptr)
	, m_pArrow(nullptr)
{
}

CPlyMagic_Arrow::~CPlyMagic_Arrow()
{
}

void CPlyMagic_Arrow::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::ARROW, false);
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_fMagicChargeTime = 1.f;
}

void CPlyMagic_Arrow::tick()
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

void CPlyMagic_Arrow::Exit()
{
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	m_fMagicChargeTime = 0.f;
}
