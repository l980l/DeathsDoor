#include "pch.h"
#include "CMagic_BombScript.h"
#include "CStateScript.h"
#include <Engine/CRenderMgr.h>
#include "CGameCameraScript.h"
#include "CLevelSaveLoadInScript.h"

CMagic_BombScript::CMagic_BombScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_BOMBSCRIPT)
	, m_fDamage(0.f)
	, m_fSpeed(800.f)
	, m_vDir{}
	, m_bThrow(false)
	, m_fPrevDirRatio(0.f)
{
}

CMagic_BombScript::~CMagic_BombScript()
{
}

void CMagic_BombScript::begin()
{
	int a = 1;
	Vec4 Color = Vec4(0.5f, 0.5f, 1.f, 1.f);
	MeshRender()->GetMaterial(0)->SetScalarParam(INT_1, &a);
	MeshRender()->GetMaterial(0)->SetScalarParam(VEC4_0, &Color);
}

void CMagic_BombScript::tick()
{
	Rigidbody()->SetGravity(0.f);
	if(m_bThrow)
	{
		Vec3 vCurVelocity = Rigidbody()->GetVelocity();
		vCurVelocity.Normalize();
		float CurVelocityRatio = vCurVelocity.x / vCurVelocity.z;
		if (m_fPrevDirRatio && abs(m_fPrevDirRatio - CurVelocityRatio) > 0.0001f)
		{
			// 방향이 바뀌면(벽이나 기타 피직스 물체에 부딪힘) 히트 이펙트 및 삭제
			Destroy();
			CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(5.f, 1000.f, 0.3f);
			// 히트 이펙트 추가할 것
		
		}
		m_fPrevDirRatio = CurVelocityRatio;
		Vec3 Velocity = m_vDir * m_fSpeed;
		Rigidbody()->SetVelocity(Velocity);
	}
}

void CMagic_BombScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetScript<CStateScript>())
	{
		if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
		{
			Stat CurStat = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
			CurStat.HP -= m_fDamage;
			_Other->GetOwner()->GetScript<CStateScript>()->SetStat(CurStat);
			Destroy();
			// 히트 이펙트 추가할 것
			CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(5.f, 1000.f, 0.3f);

			CLevelSaveLoadInScript::SpawnPrefab(L"prefab\\HitEffect.prefab", (int)LAYER::DEFAULT, Transform()->GetRelativePos(), 0.2f);
		}
	}

}

void CMagic_BombScript::EndOverlap(CCollider3D* _Other)
{
}

void CMagic_BombScript::SaveToLevelFile(FILE* _File)
{
}

void CMagic_BombScript::LoadFromLevelFile(FILE* _FILE)
{
}
