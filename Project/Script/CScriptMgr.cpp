#include "pch.h"
#include "CScriptMgr.h"

#include "CCameraMoveScript.h"
#include "CGravityScript.h"
#include "CLoadLevelThreadScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlayerScript.h"
#include "CPlayerWeaponScript.h"
#include "CPlyCharge.h"
#include "CPlyChargeAttack.h"
#include "CPlyDance.h"
#include "CPlyLadder.h"
#include "CPlyWpAttack.h"
#include "CPlyWpCharge.h"
#include "CPlyWpChargeAttack.h"
#include "CPlyWpDance.h"
#include "CPlyWpDead.h"
#include "CPlyWpDodge.h"
#include "CPlyWpFall.h"
#include "CPlyWpHit.h"
#include "CPlyWpIdle.h"
#include "CPlyWpLadder.h"
#include "CPlyWpMagic.h"
#include "CPlyWpWalk.h"
#include "CStateScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CLoadLevelThreadScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerWeaponScript");
	_vec.push_back(L"CPlyCharge");
	_vec.push_back(L"CPlyChargeAttack");
	_vec.push_back(L"CPlyDance");
	_vec.push_back(L"CPlyLadder");
	_vec.push_back(L"CPlyWpAttack");
	_vec.push_back(L"CPlyWpCharge");
	_vec.push_back(L"CPlyWpChargeAttack");
	_vec.push_back(L"CPlyWpDance");
	_vec.push_back(L"CPlyWpDead");
	_vec.push_back(L"CPlyWpDodge");
	_vec.push_back(L"CPlyWpFall");
	_vec.push_back(L"CPlyWpHit");
	_vec.push_back(L"CPlyWpIdle");
	_vec.push_back(L"CPlyWpLadder");
	_vec.push_back(L"CPlyWpMagic");
	_vec.push_back(L"CPlyWpWalk");
	_vec.push_back(L"CStateScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"CLoadLevelThreadScript" == _strScriptName)
		return new CLoadLevelThreadScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPlayerWeaponScript" == _strScriptName)
		return new CPlayerWeaponScript;
	if (L"CPlyCharge" == _strScriptName)
		return new CPlyCharge;
	if (L"CPlyChargeAttack" == _strScriptName)
		return new CPlyChargeAttack;
	if (L"CPlyDance" == _strScriptName)
		return new CPlyDance;
	if (L"CPlyLadder" == _strScriptName)
		return new CPlyLadder;
	if (L"CPlyWpAttack" == _strScriptName)
		return new CPlyWpAttack;
	if (L"CPlyWpCharge" == _strScriptName)
		return new CPlyWpCharge;
	if (L"CPlyWpChargeAttack" == _strScriptName)
		return new CPlyWpChargeAttack;
	if (L"CPlyWpDance" == _strScriptName)
		return new CPlyWpDance;
	if (L"CPlyWpDead" == _strScriptName)
		return new CPlyWpDead;
	if (L"CPlyWpDodge" == _strScriptName)
		return new CPlyWpDodge;
	if (L"CPlyWpFall" == _strScriptName)
		return new CPlyWpFall;
	if (L"CPlyWpHit" == _strScriptName)
		return new CPlyWpHit;
	if (L"CPlyWpIdle" == _strScriptName)
		return new CPlyWpIdle;
	if (L"CPlyWpLadder" == _strScriptName)
		return new CPlyWpLadder;
	if (L"CPlyWpMagic" == _strScriptName)
		return new CPlyWpMagic;
	if (L"CPlyWpWalk" == _strScriptName)
		return new CPlyWpWalk;
	if (L"CStateScript" == _strScriptName)
		return new CStateScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
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
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERWEAPONSCRIPT:
		return new CPlayerWeaponScript;
		break;
	case (UINT)SCRIPT_TYPE::PLYCHARGE:
		return new CPlyCharge;
		break;
	case (UINT)SCRIPT_TYPE::PLYCHARGEATTACK:
		return new CPlyChargeAttack;
		break;
	case (UINT)SCRIPT_TYPE::PLYDANCE:
		return new CPlyDance;
		break;
	case (UINT)SCRIPT_TYPE::PLYLADDER:
		return new CPlyLadder;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPATTACK:
		return new CPlyWpAttack;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPCHARGE:
		return new CPlyWpCharge;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPCHARGEATTACK:
		return new CPlyWpChargeAttack;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPDANCE:
		return new CPlyWpDance;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPDEAD:
		return new CPlyWpDead;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPDODGE:
		return new CPlyWpDodge;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPFALL:
		return new CPlyWpFall;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPHIT:
		return new CPlyWpHit;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPIDLE:
		return new CPlyWpIdle;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPLADDER:
		return new CPlyWpLadder;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPMAGIC:
		return new CPlyWpMagic;
		break;
	case (UINT)SCRIPT_TYPE::PLYWPWALK:
		return new CPlyWpWalk;
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

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PLAYERWEAPONSCRIPT:
		return L"CPlayerWeaponScript";
		break;

	case SCRIPT_TYPE::PLYCHARGE:
		return L"CPlyCharge";
		break;

	case SCRIPT_TYPE::PLYCHARGEATTACK:
		return L"CPlyChargeAttack";
		break;

	case SCRIPT_TYPE::PLYDANCE:
		return L"CPlyDance";
		break;

	case SCRIPT_TYPE::PLYLADDER:
		return L"CPlyLadder";
		break;

	case SCRIPT_TYPE::PLYWPATTACK:
		return L"CPlyWpAttack";
		break;

	case SCRIPT_TYPE::PLYWPCHARGE:
		return L"CPlyWpCharge";
		break;

	case SCRIPT_TYPE::PLYWPCHARGEATTACK:
		return L"CPlyWpChargeAttack";
		break;

	case SCRIPT_TYPE::PLYWPDANCE:
		return L"CPlyWpDance";
		break;

	case SCRIPT_TYPE::PLYWPDEAD:
		return L"CPlyWpDead";
		break;

	case SCRIPT_TYPE::PLYWPDODGE:
		return L"CPlyWpDodge";
		break;

	case SCRIPT_TYPE::PLYWPFALL:
		return L"CPlyWpFall";
		break;

	case SCRIPT_TYPE::PLYWPHIT:
		return L"CPlyWpHit";
		break;

	case SCRIPT_TYPE::PLYWPIDLE:
		return L"CPlyWpIdle";
		break;

	case SCRIPT_TYPE::PLYWPLADDER:
		return L"CPlyWpLadder";
		break;

	case SCRIPT_TYPE::PLYWPMAGIC:
		return L"CPlyWpMagic";
		break;

	case SCRIPT_TYPE::PLYWPWALK:
		return L"CPlyWpWalk";
		break;

	case SCRIPT_TYPE::STATESCRIPT:
		return L"CStateScript";
		break;

	}
	return nullptr;
}