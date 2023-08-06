#include "pch.h"
#include "CMoneyCountScript.h"

CMoneyCountScript::CMoneyCountScript() :
	CScript(SCRIPT_TYPE::MONEYCOUNTSCRIPT)
{
}

CMoneyCountScript::~CMoneyCountScript()
{
}

void CMoneyCountScript::begin()
{
	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}
}

void CMoneyCountScript::tick()
{
}
