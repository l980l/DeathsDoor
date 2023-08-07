#include "pch.h"
#include "CMagic_FireScript.h"
#include "CStateScript.h"

CMagic_FireScript::CMagic_FireScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_FIRESCRIPT)
{
}

CMagic_FireScript::~CMagic_FireScript()
{
}

void CMagic_FireScript::begin()
{
}

void CMagic_FireScript::tick()
{
}

void CMagic_FireScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
	{
		Stat CurStat = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		CurStat.HP -= m_fDamage;
		_Other->GetOwner()->GetScript<CStateScript>()->SetStat(CurStat);
		Destroy();
	}
}

void CMagic_FireScript::EndOverlap(CCollider3D* _Other)
{
}

void CMagic_FireScript::SaveToLevelFile(FILE* _File)
{
}

void CMagic_FireScript::LoadFromLevelFile(FILE* _FILE)
{
}
