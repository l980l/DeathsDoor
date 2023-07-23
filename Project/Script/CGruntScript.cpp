#include "pch.h"
#include "CGruntScript.h"
#include "CStateScript.h"

void CGruntScript::begin()
{
}

void CGruntScript::tick()
{
}

void CGruntScript::BeginOverlap(CCollider3D* _Other)
{
}

void CGruntScript::SaveToLevelFile(FILE* _File)
{
}

void CGruntScript::LoadFromLevelFile(FILE* _File)
{
}

CGruntScript::CGruntScript() :
	CMonsterScript((UINT)SCRIPT_TYPE::GRUNTSCRIPT)
{
}

CGruntScript::CGruntScript(const CGruntScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::GRUNTSCRIPT)
{
}

CGruntScript::~CGruntScript()
{
}
