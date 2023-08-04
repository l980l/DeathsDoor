#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	ANCHORSCRIPT,
	ARROWICONSCRIPT,
	BANKERFRAMESCRIPT,
	BANKNPCSCRIPT,
	BANKUPGRADESCRIPT,
	BATSCRIPT,
	BAZOOKASCRIPT,
	BOMBICONSCRIPT,
	BRAZIERSCRIPT,
	CAMERAMOVESCRIPT,
	CROWBOSSSCRIPT,
	CROWHEADSCRIPT,
	CURSORSCRIPT,
	ENERGYICONSCRIPT,
	ENTERSCRIPT,
	FENSESCRIPT,
	FIREICONSCRIPT,
	GAMECAMERASCRIPT,
	GHOSTSCRIPT,
	GRAVITYSCRIPT,
	GRIMKNIGHTSCRIPT,
	GRUNTSCRIPT,
	HITSTONESCRIPT,
	HOOKICONSCRIPT,
	HPICONSCRIPT,
	HUDSCRIPT,
	KNIGHTSCRIPT,
	LOADLEVELTHREADSCRIPT,
	LURKERSCRIPT,
	MAGIC_ARROWSCRIPT,
	MAGIC_BOMBSCRIPT,
	MAGIC_FIRESCRIPT,
	MAGIC_HOOKSCRIPT,
	MISSILESCRIPT,
	MONEYCOUNTSCRIPT,
	MONSTERDETECTRANGESCRIPT,
	NAVITESTSCRIPT,
	PLAYERSCRIPT,
	PLAYERWEAPONSCRIPT,
	ROOMSCRIPT,
	SPAWNDOORSCRIPT,
	STATESCRIPT,
	WALLSCRIPT,
	WATERCAMERASCRIPT,
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
