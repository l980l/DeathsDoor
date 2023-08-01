#include "pch.h"
#include "CMagic_BombScript.h"

CMagic_BombScript::CMagic_BombScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_BOMBSCRIPT)
{
}

CMagic_BombScript::~CMagic_BombScript()
{
}

void CMagic_BombScript::begin()
{
}

void CMagic_BombScript::tick()
{
}

void CMagic_BombScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
		Destroy();
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
