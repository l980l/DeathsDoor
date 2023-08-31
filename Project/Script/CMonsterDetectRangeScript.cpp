#include "pch.h"
#include "CMonsterDetectRangeScript.h"
#include "CMonsterScript.h"

CMonsterDetectRangeScript::CMonsterDetectRangeScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERDETECTRANGESCRIPT)
{
}

CMonsterDetectRangeScript::~CMonsterDetectRangeScript()
{
}

void CMonsterDetectRangeScript::begin()
{
}

void CMonsterDetectRangeScript::tick()
{
}

void CMonsterDetectRangeScript::BeginOverlap(CCollider3D* _Other)
{
	// Player¿Í ºÎµúÈù °æ¿ì¿¡¸¸.
	if (_Other->GetOwner()->GetLayerIndex()	== (int)LAYER::PLAYER)
	{
		GetOwner()->GetParent()->GetScript<CMonsterScript>()->SetDetect(true);
		Destroy();
	}
}
