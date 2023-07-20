#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	CAMERAMOVESCRIPT,
	GRAVITYSCRIPT,
	LOADLEVELTHREADSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	PLAYERSCRIPT,
	PLAYERWEAPONSCRIPT,
	PLYCHARGE,
	PLYCHARGEATTACK,
	PLYDANCE,
	PLYLADDER,
	PLYWPATTACK,
	PLYWPCHARGE,
	PLYWPCHARGEATTACK,
	PLYWPDANCE,
	PLYWPDEAD,
	PLYWPDODGE,
	PLYWPFALL,
	PLYWPHIT,
	PLYWPIDLE,
	PLYWPLADDER,
	PLYWPMAGIC,
	PLYWPWALK,
	STATESCRIPT,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
