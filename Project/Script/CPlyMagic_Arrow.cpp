#include "pch.h"
#include "CPlyMagic_Arrow.h"
#include <Engine/CDevice.h>
#include "CLevelSaveLoadInScript.h"
#include "CPlayerScript.h"
#include "CMagic_ArrowScript.h"

CPlyMagic_Arrow::CPlyMagic_Arrow()
{
}

CPlyMagic_Arrow::~CPlyMagic_Arrow()
{
}

void CPlyMagic_Arrow::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::ARROW, false);
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.04f, 0.04f, 0.04f);
	GetOwner()->GetChild()[1]->Transform()->SetRelativeRot(XM_PI / 2.f, XM_PI, XM_PI / 2.f);
	GetOwner()->GetChild()[1]->Transform()->SetRelativePos(Vec3(0.f, 1.f, 1.f));
}

void CPlyMagic_Arrow::tick()
{
	if (KEY_PRESSED(KEY::RBTN))
	{
		CalcDir();

	}
	if (GetOwner()->Animator3D()->IsFinish())
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();
			Vec3 vDir = GetOwner()->Transform()->GetXZDir();
			CLevelSaveLoadInScript script;
			Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 40.f, CurPos.z) + vDir * 40.f;
			CGameObject* pArrow = script.SpawnandReturnPrefab(L"prefab\\Arrow.prefab", (int)LAYER::PLAYERPROJECTILE, vSpawnPos);
			pArrow->GetScript<CMagic_ArrowScript>()->SetDir(vDir);
			pArrow->GetScript<CMagic_ArrowScript>()->SetStartPos(vSpawnPos);
			pArrow->Transform()->SetRelativeRot(m_vAttackDir);
			pArrow->Transform()->SetRelativeScale(Vec3(0.4f));

			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
	else
	{
		if (KEY_RELEASE(KEY::RBTN))
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
	}
}

void CPlyMagic_Arrow::Exit()
{
	GetOwner()->GetChild()[1]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
}

void CPlyMagic_Arrow::CalcDir()
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	m_vAttackDir = Vec3(XM_2PI - XM_PI * 1.5f,fRot, XM_2PI);
}
