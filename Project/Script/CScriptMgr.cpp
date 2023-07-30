#include "pch.h"
#include "CScriptMgr.h"

#include "CAnchorScript.h"
#include "CBazookaScript.h"
#include "CBrazierScript.h"
#include "CCameraMoveScript.h"
#include "CCrowBossScript.h"
#include "CCrowHeadScript.h"
#include "CGameCameraScript.h"
#include "CGravityScript.h"
#include "CGruntScript.h"
#include "CLoadLevelThreadScript.h"
#include "CLurkerScript.h"
#include "CMagic_ArrowScript.h"
#include "CMagic_BombScript.h"
#include "CMagic_FireScript.h"
#include "CMagic_HookScript.h"
#include "CMissileScript.h"
#include "CMonsterDetectRangeScript.h"
#include "CPlayerScript.h"
#include "CPlayerWeaponScript.h"
#include "CStateScript.h"
#include "CWindShaderScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CAnchorScript");
	_vec.push_back(L"CBankerFrameScript");
	_vec.push_back(L"CBankerScript");
	_vec.push_back(L"CBazookaScript");
	_vec.push_back(L"CBrazierScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCrowBossScript");
	_vec.push_back(L"CCrowHeadScript");
	_vec.push_back(L"CGameCameraScript");
	_vec.push_back(L"CGhostScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CGrimKnightScript");
	_vec.push_back(L"CGruntScript");
	_vec.push_back(L"CKnightScript");
	_vec.push_back(L"CLoadLevelThreadScript");
	_vec.push_back(L"CLurkerScript");
	_vec.push_back(L"CMagic_ArrowScript");
	_vec.push_back(L"CMagic_BombScript");
	_vec.push_back(L"CMagic_FireScript");
	_vec.push_back(L"CMagic_HookScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterDetectRangeScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerWeaponScript");
	_vec.push_back(L"CStateScript");
	_vec.push_back(L"CWindShaderScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CAnchorScript" == _strScriptName)
		return new CAnchorScript;
	if (L"CBazookaScript" == _strScriptName)
		return new CBazookaScript;
	if (L"CBrazierScript" == _strScriptName)
		return new CBrazierScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCrowBossScript" == _strScriptName)
		return new CCrowBossScript;
	if (L"CCrowHeadScript" == _strScriptName)
		return new CCrowHeadScript;
	if (L"CGameCameraScript" == _strScriptName)
		return new CGameCameraScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"CGruntScript" == _strScriptName)
		return new CGruntScript;
	if (L"CLoadLevelThreadScript" == _strScriptName)
		return new CLoadLevelThreadScript;
	if (L"CLurkerScript" == _strScriptName)
		return new CLurkerScript;
	if (L"CMagic_ArrowScript" == _strScriptName)
		return new CMagic_ArrowScript;
	if (L"CMagic_BombScript" == _strScriptName)
		return new CMagic_BombScript;
	if (L"CMagic_FireScript" == _strScriptName)
		return new CMagic_FireScript;
	if (L"CMagic_HookScript" == _strScriptName)
		return new CMagic_HookScript;
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
	if (L"CWindShaderScript" == _strScriptName)
		return new CWindShaderScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::ANCHORSCRIPT:
		return new CAnchorScript;
		break;
	case (UINT)SCRIPT_TYPE::BAZOOKASCRIPT:
		return new CBazookaScript;
		break;
	case (UINT)SCRIPT_TYPE::BRAZIERSCRIPT:
		return new CBrazierScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CROWBOSSSCRIPT:
		return new CCrowBossScript;
		break;
	case (UINT)SCRIPT_TYPE::CROWHEADSCRIPT:
		return new CCrowHeadScript;
		break;
	case (UINT)SCRIPT_TYPE::GAMECAMERASCRIPT:
		return new CGameCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::GRAVITYSCRIPT:
		return new CGravityScript;
		break;
	case (UINT)SCRIPT_TYPE::GRUNTSCRIPT:
		return new CGruntScript;
		break;
	case (UINT)SCRIPT_TYPE::LOADLEVELTHREADSCRIPT:
		return new CLoadLevelThreadScript;
		break;
	case (UINT)SCRIPT_TYPE::LURKERSCRIPT:
		return new CLurkerScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGIC_ARROWSCRIPT:
		return new CMagic_ArrowScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGIC_BOMBSCRIPT:
		return new CMagic_BombScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGIC_FIRESCRIPT:
		return new CMagic_FireScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGIC_HOOKSCRIPT:
		return new CMagic_HookScript;
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
	case (UINT)SCRIPT_TYPE::WINDSHADERSCRIPT:
		return new CWindShaderScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::ANCHORSCRIPT:
		return L"CAnchorScript";
		break;

	case SCRIPT_TYPE::BAZOOKASCRIPT:
		return L"CBazookaScript";
		break;

	case SCRIPT_TYPE::BRAZIERSCRIPT:
		return L"CBrazierScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CROWBOSSSCRIPT:
		return L"CCrowBossScript";
		break;

	case SCRIPT_TYPE::CROWHEADSCRIPT:
		return L"CCrowHeadScript";
		break;

	case SCRIPT_TYPE::GAMECAMERASCRIPT:
		return L"CGameCameraScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"CGravityScript";
		break;

	case SCRIPT_TYPE::GRUNTSCRIPT:
		return L"CGruntScript";
		break;

	case SCRIPT_TYPE::LOADLEVELTHREADSCRIPT:
		return L"CLoadLevelThreadScript";
		break;

	case SCRIPT_TYPE::LURKERSCRIPT:
		return L"CLurkerScript";
		break;

	case SCRIPT_TYPE::MAGIC_ARROWSCRIPT:
		return L"CMagic_ArrowScript";
		break;

	case SCRIPT_TYPE::MAGIC_BOMBSCRIPT:
		return L"CMagic_BombScript";
		break;

	case SCRIPT_TYPE::MAGIC_FIRESCRIPT:
		return L"CMagic_FireScript";
		break;

	case SCRIPT_TYPE::MAGIC_HOOKSCRIPT:
		return L"CMagic_HookScript";
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

	case SCRIPT_TYPE::WINDSHADERSCRIPT:
		return L"CWindShaderScript";
		break;

	}
	return nullptr;
}