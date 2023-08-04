#include "pch.h"
#include "CFenseScript.h"

CFenseScript::CFenseScript() :
	CScript(SCRIPT_TYPE::FENSESCRIPT)
{
}

CFenseScript::~CFenseScript()
{
}

void CFenseScript::begin()
{
}

void CFenseScript::tick()
{
}

void CFenseScript::BeginOverlap(CCollider3D* _Other)
{
}

void CFenseScript::OnOverlap(CCollider3D* _Other)
{
}

void CFenseScript::EndOverlap(CCollider3D* _Other)
{
}
