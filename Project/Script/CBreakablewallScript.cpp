#include "pch.h"
#include "CBreakablewallScript.h"

CBreakablewallScript::CBreakablewallScript()
	: CScript((UINT)SCRIPT_TYPE::BREAKABLEWALLSCRIPT)
{
}

CBreakablewallScript::~CBreakablewallScript()
{
}

void CBreakablewallScript::begin()
{
}

void CBreakablewallScript::tick()
{
}

void CBreakablewallScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBreakablewallScript::EndOverlap(CCollider3D* _Other)
{
}

void CBreakablewallScript::SaveToLevelFile(FILE* _File)
{
}

void CBreakablewallScript::LoadFromLevelFile(FILE* _FILE)
{
}
