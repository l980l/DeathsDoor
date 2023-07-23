#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	ANCHORSCRIPT,
	BAZOOKASCRIPT,
	BRAZIERSCRIPT,
	BREAKABLEWALLSCRIPT,
	CAMERAMOVESCRIPT,
	GAMECAMERASCRIPT,
	GRAVITYSCRIPT,
	LOADLEVELTHREADSCRIPT,
	MAGIC_ARROWSCRIPT,
	MAGIC_BOMBSCRIPT,
	MAGIC_FIRESCRIPT,
	MAGIC_HOOKSCRIPT,
	MISSILESCRIPT,
	MONSTERDETECTRANGESCRIPT,
	PLAYERSCRIPT,
	PLAYERWEAPONSCRIPT,
	STATESCRIPT,
	AGICFUNC,
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
