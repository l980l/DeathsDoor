#include "pch.h"
#include "CMagic_FireScript.h"

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
		Destroy();
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
