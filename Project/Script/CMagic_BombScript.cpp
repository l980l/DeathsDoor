#include "pch.h"
#include "CMagic_BombScript.h"
#include "CStateScript.h"

CMagic_BombScript::CMagic_BombScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_BOMBSCRIPT)
	, m_fDamage(0.f)
{
}

CMagic_BombScript::~CMagic_BombScript()
{
}

void CMagic_BombScript::begin()
{
	int a = 1;
	Vec4 Color = Vec4(0.4f, 0.4f, 1.f, 1.f);
	MeshRender()->GetMaterial(0)->SetScalarParam(INT_1, &a);
	MeshRender()->GetMaterial(0)->SetScalarParam(VEC4_0, &Color);
}

void CMagic_BombScript::tick()
{
}

void CMagic_BombScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
	{
		Stat CurStat = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		CurStat.HP -= m_fDamage;
		_Other->GetOwner()->GetScript<CStateScript>()->SetStat(CurStat);
		Destroy();
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
