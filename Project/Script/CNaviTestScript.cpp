#include "pch.h"
#include "CNaviTestScript.h"
#include "CStateScript.h"
#include "CTrace.h"

CNaviTestScript::CNaviTestScript()
	:CScript((UINT)SCRIPT_TYPE::NAVITESTSCRIPT)
{
}

CNaviTestScript::~CNaviTestScript()
{
}

void CNaviTestScript::begin()
{
	m_pStateScript = GetOwner()->GetScript<CStateScript>();
	m_pStateScript->AddState(L"Trace", new CTrace);
	m_pStateScript->ChangeState(L"Trace");
}

void CNaviTestScript::tick()
{
}
