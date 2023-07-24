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
	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();
	}
	m_fMagicChargeTime -= DT;
	if (m_fMagicChargeTime <= 0.f)
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			Ptr<CPrefab> pArrowPref = CResMgr::GetInst()->FindRes<CPrefab>(L"prefab\Arrow.prefab");
			CGameObject* pArrow = pArrowPref->Instantiate();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			pArrow->Rigidbody()->AddVelocity(vDir * 800.f);
			pArrow->SetLifeSpan(3.f);
		}
	}
}

void CPlyMagic_Arrow::Exit()
{
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	m_fMagicChargeTime = 0.f;
}

void CPlyMagic_Arrow::CalcDir()
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
}
