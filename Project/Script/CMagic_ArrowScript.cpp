#include "pch.h"
#include "CMagic_ArrowScript.h"

CMagic_ArrowScript::CMagic_ArrowScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_ARROWSCRIPT)
{
}

CMagic_ArrowScript::~CMagic_ArrowScript()
{
}
void CMagic_ArrowScript::begin()
{
	Rigidbody()->SetVelocityLimit(1200.f);
	Rigidbody()->SetFriction(0.f);
	Rigidbody()->SetMass(1.f);
	Rigidbody()->SetFrictionScale(1.f);
}

void CMagic_ArrowScript::tick()
{
}

void CMagic_ArrowScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
		Destroy();
	// 터지는 효과 등 나오게 할 것
}

void CMagic_ArrowScript::EndOverlap(CCollider3D* _Other)
{
}


void CMagic_ArrowScript::SaveToLevelFile(FILE* _File)
{
}

void CMagic_ArrowScript::LoadFromLevelFile(FILE* _FILE)
{
}

