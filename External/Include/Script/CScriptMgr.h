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
	CROWBOSSSCRIPT,
	GRAVITYSCRIPT,
	GRUNTSCRIPT,
	LOADLEVELTHREADSCRIPT,
	LURKERSCRIPT,
	MISSILESCRIPT,
	MONSTERDETECTRANGESCRIPT,
	PLAYERSCRIPT,
	PLAYERWEAPONSCRIPT,
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
