#include "pch.h"
#include "CScriptMgr.h"

#include "CBazookaScript.h"
#include "CCameraMoveScript.h"
#include "CGravityScript.h"
#include "CLoadLevelThreadScript.h"
#include "CMissileScript.h"
#include "CMonsterDetectRangeScript.h"
#include "CPlayerScript.h"
#include "CPlayerWeaponScript.h"
#include "CStateScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBazookaScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CLoadLevelThreadScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterDetectRangeScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerWeaponScript");
	_vec.push_back(L"CStateScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBazookaScript" == _strScriptName)
		return new CBazookaScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"CLoadLevelThreadScript" == _strScriptName)
		return new CLoadLevelThreadScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterDetectRangeScript" == _strScriptName)
		return new CMonsterDetectRangeScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPlayerWeaponScript" == _strScriptName)
		return new CPlayerWeaponScript;
	if (L"CStateScript" == _strScriptName)
		return new CStateScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BAZOOKASCRIPT:
		return new CBazookaScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::GRAVITYSCRIPT:
		return new CGravityScript;
		break;
	case (UINT)SCRIPT_TYPE::LOADLEVELTHREADSCRIPT:
		return new CLoadLevelThreadScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERDETECTRANGESCRIPT:
		return new CMonsterDetectRangeScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERWEAPONSCRIPT:
		return new CPlayerWeaponScript;
		break;
	case (UINT)SCRIPT_TYPE::STATESCRIPT:
		return new CStateScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BAZOOKASCRIPT:
		return L"CBazookaScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"CGravityScript";
		break;

	case SCRIPT_TYPE::LOADLEVELTHREADSCRIPT:
		return L"CLoadLevelThreadScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERDETECTRANGESCRIPT:
		return L"CMonsterDetectRangeScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PLAYERWEAPONSCRIPT:
		return L"CPlayerWeaponScript";
		break;

	case SCRIPT_TYPE::STATESCRIPT:
		return L"CStateScript";
		break;

	}
	return nullptr;
}